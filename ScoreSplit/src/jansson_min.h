#pragma once

#define DLLIMPORT __declspec(dllimport)

typedef enum {
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_STRING,
    JSON_INTEGER,
    JSON_REAL,
    JSON_TRUE,
    JSON_FALSE,
    JSON_NULL
} json_type;

typedef struct json_t {
    json_type type;
    volatile size_t refcount;
} json_t;

extern "C" {
    DLLIMPORT json_t* json_object();

    DLLIMPORT void json_delete(json_t* json);
    static inline void json_decref(json_t* json) {
        if (json && json->refcount != (size_t)-1 && --json->refcount == 0)
            json_delete(json);
    }

    DLLIMPORT json_t* json_string(const char* value);
    DLLIMPORT json_t* json_integer(long long value);

    DLLIMPORT int json_object_set_new(json_t* object, const char* key, json_t* value);

    DLLIMPORT char* json_dumps(const json_t* json, size_t flags);
}

inline void json_object_set_new_opt_str(json_t* writer, const char* key, const char* value) {
    if (value && value[0])
        json_object_set_new(writer, key, json_string(value));
}
