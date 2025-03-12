#include "postgres.h"
#include "fmgr.h"
#include "utils/uuid.h"
#include "utils/builtins.h"
#include "utils/bytea.h"
#include "utils/array.h"
#include "utils/elog.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

void decode_onec_uuid(unsigned char *src, unsigned char *dst)
{
    if (src == NULL || dst == NULL) {
        return;        
    }

    // Копируем последние 4 байта в начало
    memcpy(dst, src + 12, 4);
    // Копируем байты 10-11 в позицию 4-5
    memcpy(dst + 4, src + 10, 2);
    // Копируем байты 8-9 в позицию 6-7
    memcpy(dst + 6, src + 8, 2);
    // Копируем первые 8 байт в конец
    memcpy(dst + 8, src, 8);
}

void encode_onec_uuid(unsigned char *src, unsigned char *dst)
{
    if (src == NULL || dst == NULL) {
        return;        
    }

    // Копируем байты 8-11 в начало
    memcpy(dst, src + 8, 4);
    // Копируем байты 12-15 в позицию 4-7
    memcpy(dst + 4, src + 12, 4);
    // Копируем байты 6-7 в позицию 8-9
    memcpy(dst + 8, src + 6, 2);
    // Копируем байты 4-5 в позицию 10-11
    memcpy(dst + 10, src + 4, 2);
    // Копируем первые 4 байта в конец
    memcpy(dst + 12, src, 4);
}


PG_FUNCTION_INFO_V1(onec_decode_uuid);
Datum
onec_decode_uuid(PG_FUNCTION_ARGS)
{
    pg_uuid_t *uuid = (pg_uuid_t *) palloc(sizeof(*uuid));

    if (PG_ARGISNULL(0)) {
        // Если аргумент NULL, возвращаем нулевой UUID      
        memset(&uuid->data, 0, UUID_LEN);
        PG_RETURN_UUID_P(uuid);
    }

    bytea *id = PG_GETARG_BYTEA_P(0);
    int len = VARSIZE(id) - VARHDRSZ;

    if (len < 16) {
        memset(&uuid->data, 0, UUID_LEN);
        PG_RETURN_UUID_P(uuid);
    }

    unsigned char *data = (unsigned char*) VARDATA(id);

    decode_onec_uuid(data, uuid->data);

    PG_RETURN_UUID_P(uuid);
}

PG_FUNCTION_INFO_V1(onec_encode_uuid);
Datum
onec_encode_uuid(PG_FUNCTION_ARGS)
{
    pg_uuid_t *uuid;
    bytea *result;
    
    if (PG_ARGISNULL(0)) {
        PG_RETURN_NULL();
    }

    uuid = PG_GETARG_UUID_P(0);
    
    // Выделяем память под результат
    result = (bytea *) palloc(VARHDRSZ + 16);
    SET_VARSIZE(result, VARHDRSZ + 16);
    
    // Кодируем UUID в формат 1С
    encode_onec_uuid(uuid->data, (unsigned char *) VARDATA(result));
    
    PG_RETURN_BYTEA_P(result);
}
