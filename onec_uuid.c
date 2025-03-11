#include "postgres.h"
#include "fmgr.h"
#include "utils/uuid.h"
#include "utils/builtins.h"
#include "utils/bytea.h"
#include "utils/array.h"
#include "utils/elog.h"


/*#if defined(HAVE_UUID_H)
#include <uuid.h>
#elif defined(HAVE_OSSP_UUID_H)
#include <ossp/uuid.h>
#elif defined(HAVE_UUID_UUID_H)
#include <uuid/uuid.h>
#else
#error "please use configure's --with-uuid switch to select a UUID library"
#endif
*/

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

PG_FUNCTION_INFO_V1(onec_extract_uuid);

Datum
onec_extract_uuid(PG_FUNCTION_ARGS)
{
    bytea *id = PG_GETARG_BYTEA_P(0);
    pg_uuid_t *uuid = (pg_uuid_t *) palloc(sizeof(*uuid));

    if (id == NULL ) {
        // Если id NULL, возвращаем нулевой UUID      
        elog(ERROR,"id is not null");
        memset(&uuid->data, 0, UUID_LEN);
    }else {

        int len = VARSIZE(id) - VARHDRSZ;

	if (len < 16) {
    	    elog(ERROR,"len < 16");
        }

        // Получаем указатель на данные bytea
        //char *data = VARDATA_ANY(id); 

	//elog(INFO,"start parsing, %x", 0x20);

	unsigned char *data = (unsigned char*) VARDATA(id);

	uuid->data[0] = data[12];
	uuid->data[1] = data[13];
        uuid->data[2] = data[14];
        uuid->data[3] = data[15];
        uuid->data[4] = data[10];
        uuid->data[5] = data[11];
        uuid->data[6] = data[8];
        uuid->data[7] = data[9];
        uuid->data[8] = data[0];
        uuid->data[9] = data[1];
        uuid->data[10] = data[2];
        uuid->data[11] = data[3];
        uuid->data[12] = data[4];
        uuid->data[13] = data[5];
        uuid->data[14] = data[6];
        uuid->data[15] = data[7];

	/*for(int i=0;i<16;i++) {
	 elog(INFO,"data[%d] = %x",i,uuid->data[i]);
	}*/


        // Проверяем, что длина bytea достаточна
/*        if (len >= 16) {
            // Извлекаем необходимые байты и формируем UUID
            uint32_t time_low = *((uint32_t *)(data + 12));
            uint16_t time_mid = *((uint16_t *)(data + 10));
            uint16_t time_hi_and_version = *((uint16_t *)(data + 8));
            uint8_t clock_seq_hi_and_reserved = *(data + 7);
            uint8_t clock_seq_low = *(data + 6);
            uint8_t node[6];
            memcpy(node, data + 0, 6);

            // Формируем UUID
            memcpy(&result, &time_low, sizeof(time_low));
            memcpy((char *)&result + 4, &time_mid, sizeof(time_mid));
            memcpy((char *)&result + 6, &time_hi_and_version, sizeof(time_hi_and_version));
            memcpy((char *)&result + 8, &clock_seq_hi_and_reserved, sizeof(clock_seq_hi_and_reserved));
            memcpy((char *)&result + 9, &clock_seq_low, sizeof(clock_seq_low));
            memcpy((char *)&result + 10, node, sizeof(node));
        } else {
            // Если длина недостаточна, возвращаем нулевой UUID
            memset(&uuid->data, 0, sizeof(result));
        }*/
    }

    PG_RETURN_UUID_P(uuid);
}
