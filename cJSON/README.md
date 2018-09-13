# how to build cJSON library
https://github.com/DaveGamble/cJSON

# how to compile test
> gcc -o test cjson_test.c cJSON.o

# study
## Usage
* create Object or Array
  * add
    * addTypesToObject (12) : 9Type + Bool + Item + ItemToObjectCS
    * addItemToArray (1) 
    * addReferenceItem (2) : toObject or toArray
  * delete
    * deleteItemFrom (3) : Array, Object, ObjectCaseSensitive

## 9 Types
1. invalid
2. false
3. true
4. null
5. number
6. string
7. array
8. object
9. raw


## Node structure
* prev,next,child
* type
* string
* valuestring, valueint, valuedouble
