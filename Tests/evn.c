#include "shell.h"
#include "funcs.h"

/**
 * The function correctly fills the environment 
 * linked list with all the environment variables.
*/
void test_fillEnvList_success()
{
    PassInfo data;
    data.env = NULL;
    int result = fillEnvList(&data);
    String_t *node = data.env;
    int count = 0;
    while (node != NULL) {
        count++;
        node = node->next;
    }
    
    /*Assuming there are 3 environmental variables*/
    TEST_ASSERT_EQUAL_INT(3, count); 
    TEST_ASSERT_EQUAL_INT(0, result);
}
