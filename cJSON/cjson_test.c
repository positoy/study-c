#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"

/*
{
    "name" : "bitcomputer"
    "courses" : [
        {
            "name" : "c++",
            "instructor" : "changkyu",
            "cost" : 200000,
            "students" : ["changkyu","jonghyun","jinhong","sekyoung"]
        },
        {
            "name" : "nodejs",
            "instructor" : "changkyu",
            "cost" : 300000,
            "students" : ["hello","world"]
        }
    ]
}
*/

int main()
{
    // practice cJSON
    puts(cJSON_Version());

    cJSON* jobject = cJSON_CreateObject();
    cJSON_AddStringToObject(jobject,"name","bitcomputer");
    cJSON* jobject_courses = cJSON_AddArrayToObject(jobject, "courses");

    cJSON* cOjbect = cJSON_CreateObject();
    cJSON_AddStringToObject(cOjbect, "name", "c++");
    cJSON_AddStringToObject(cOjbect, "instructor", "changkyu");

    cJSON* jobject_courses_students = cJSON_AddArrayToObject(cOjbect, "students");
    cJSON_AddItemToArray(jobject_courses_students, cJSON_CreateString("changkyu"));
    cJSON_AddItemToArray(jobject_courses_students, cJSON_CreateString("jonghyun"));
    cJSON_AddItemToArray(jobject_courses_students, cJSON_CreateString("jinhong"));
    cJSON_AddItemToArray(jobject_courses_students, cJSON_CreateString("sekyoung"));

    cJSON_AddItemToArray(jobject_courses, cOjbect);

    cOjbect = cJSON_CreateObject();
    cJSON_AddStringToObject(cOjbect, "name", "nodejs");
    cJSON_AddStringToObject(cOjbect, "instructor", "changkyu");

    jobject_courses_students = cJSON_AddArrayToObject(cOjbect, "students");
    cJSON_AddItemToArray(jobject_courses_students, cJSON_CreateString("hello"));
    cJSON_AddItemToArray(jobject_courses_students, cJSON_CreateString("world"));

    cJSON_AddItemToArray(jobject_courses, cOjbect);

    char* result = cJSON_Print(jobject);
    puts(result);
}
