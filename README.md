# PostgreSQL 1C UUID Converter

Расширение для конвертации UUID между форматами PostgreSQL и 1C.

## Описание

Расширение предоставляет функции для конвертации UUID между форматами PostgreSQL и 1C:

- `onec_decode_uuid(bytea)` - преобразует UUID из формата 1C в формат PostgreSQL
- `onec_encode_uuid(uuid)` - преобразует UUID из формата PostgreSQL в формат 1C

## Требования

- PostgreSQL 12 или выше
- Заголовочные файлы PostgreSQL
- Компилятор GCC

## Установка

1. Клонируйте репозиторий
2. Соберите и установите расширение:

```bash
make USE_PGXS=1
make USE_PGXS=1 install
```

3. В базе данных PostgreSQL выполните:
```sql
CREATE EXTENSION onec_uuid;
```

## Примеры использования

```sql
-- Конвертация из формата 1C в PostgreSQL
SELECT onec_decode_uuid('\x1234567890ABCDEF1234567890ABCDEF'::bytea);

-- Конвертация из PostgreSQL в формат 1C
SELECT onec_encode_uuid('12345678-90ab-cdef-1234-567890abcdef'::uuid);
```

## Особенности

- Безопасная обработка NULL значений
- Оптимизированное копирование данных
- Проверка корректности входных данных
- Поддержка всех версий PostgreSQL 12+

## Разработка

Для сборки в режиме разработки:

```bash
make clean
make
```

## Лицензия

BSD
