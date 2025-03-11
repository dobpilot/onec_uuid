\echo Use "CREATE EXTENSION onec_uuid" to load this file. \quit


CREATE OR REPLACE FUNCTION onec_extract_uuid(bytea)
RETURNS uuid AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE;
