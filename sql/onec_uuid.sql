CREATE EXTENSION onec_uuid;

select onec_decode_uuid(decode('80c3251185ce937342066c99c815dde9', 'hex')) = 'c815dde9-6c99-4206-80c3-251185ce9373' as "true";

select encode(onec_encode_uuid('c815dde9-6c99-4206-80c3-251185ce9373'),'hex') = '80c3251185ce937342066c99c815dde9' as "true";

select onec_decode_uuid(null) = '00000000-0000-0000-0000-000000000000' as "true";

select onec_encode_uuid(null) = null as "true";