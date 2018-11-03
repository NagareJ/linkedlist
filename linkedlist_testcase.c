#include <gtest/gtest.h>
#include "linked_list.h"

TEST(AddToListTest, NormalTest)
{
	int result;
	linked_list* pHead = (linked_list*)malloc(sizeof(linked_list));
	pHead->data = NULL;
	pHead->next = NULL;
	pHead->index = 0;

	result = add_to_list(pHead, (char *) "a21321321AAA@@@1");

	ASSERT_EQ(result, 1);
	ASSERT_STREQ((char *)"a21321321AAA@@@1", pHead->next->data);



	result = add_to_list(pHead, (char *) "a123AAA2213213@@@@@!!!!!!!");
	ASSERT_EQ(result, 2);
	ASSERT_STREQ((char *)"a123AAA2213213@@@@@!!!!!!!", pHead->next->next->data);


}


TEST(DisplayItem, NormalTest)
{
	int result;
	linked_list* pHead = (linked_list*)malloc(sizeof(linked_list));
	pHead->data = NULL;
	pHead->next = NULL;

	result = display_item(pHead);
	ASSERT_EQ(result, -1);

	printf("\n----\n");

	pHead->data = (char *)"a123AAA2213213@@@@@!!!!!!!";
	result = display_item(pHead);
	ASSERT_EQ(result, 0);

	printf("\n----\n");

	pHead->data = (char *)"a123AAA2213213@@@@@!!!!!!!a123AAA2213213@@@@@!!!!!!!";
	result = display_item(pHead);
	ASSERT_EQ(result, 0);

	printf("\n----\n");
}

TEST(DisplayList, NormalTest)
{
	linked_list *pHead = (linked_list*)malloc(sizeof(linked_list));
	pHead->next = NULL;
	pHead->data = NULL;


	ASSERT_EQ(0, display_list(pHead));



	pHead->next = (linked_list*)malloc(sizeof(linked_list));
	pHead->next->next = NULL;
	pHead->next->data = (char *)"layer 1";
	ASSERT_EQ(1, display_list(pHead));

	printf("\n----\n");

	pHead->next->next = (linked_list*)malloc(sizeof(linked_list));
	pHead->next->next->next = NULL;
	pHead->next->next->data = (char *)"layer 2";
	ASSERT_EQ(2, display_list(pHead));

	printf("\n----\n");

	pHead->next->next->next = (linked_list*)malloc(sizeof(linked_list));
	pHead->next->next->next->next = NULL;
	pHead->next->next->next->data = (char *)"layer 3";
	ASSERT_EQ(3, display_list(pHead));
}

TEST(SearchFromList, NormalTest)
{
	int result;
	linked_list *pHead = (linked_list*)malloc(sizeof(linked_list));
	linked_list *tmp;

	pHead->next = (linked_list*)malloc(sizeof(linked_list));
	pHead->next->next = (linked_list*)malloc(sizeof(linked_list));
	pHead->next->next->next = (linked_list*)malloc(sizeof(linked_list));
	pHead->next->next->next->next = NULL;


	pHead->next->data = (char *)"layer 1";
	pHead->next->next->data = (char*)"layer 2";
	pHead->next->next->next->data = (char*)"layer 3";


	tmp = search_from_list(pHead, (char *)"layer 4");
	ASSERT_EQ(NULL, tmp);


	tmp = search_from_list(pHead, (char *)"layer 1");
	ASSERT_STREQ(tmp->data, pHead->next->data);
	ASSERT_EQ(tmp->next, pHead->next->next);

	tmp = search_from_list(pHead, (char *)"layer 2");
	ASSERT_STREQ(tmp->data, pHead->next->next->data);
	ASSERT_EQ(tmp->next, pHead->next->next->next);

	tmp = search_from_list(pHead, (char *) "layer 3");
	ASSERT_STREQ(tmp->data, pHead->next->next->next->data);
	ASSERT_EQ(tmp->next, pHead->next->next->next->next);

}



TEST(DeleteFromList, NormalTest)
{
	linked_list *pHead = (linked_list*)malloc(sizeof(linked_list));

	pHead->next = (linked_list*)malloc(sizeof(linked_list));
	pHead->next->next = (linked_list*)malloc(sizeof(linked_list));
	pHead->next->next->next = (linked_list*)malloc(sizeof(linked_list));
	pHead->next->next->next->next = NULL;


	pHead->next->data = (char *)"layer 1";
	pHead->next->next->data = (char *)"layer 2";
	pHead->next->next->next->data = (char *)"layer 3";

	pHead->next->index = 1;
	pHead->next->next->index = 2;
	pHead->next->next->next->index = 3;


	ASSERT_EQ(2, delete_from_list(pHead, 1));
	ASSERT_EQ(1, delete_from_list(pHead, 2));
	ASSERT_EQ(-1, delete_from_list(pHead, 4));
	ASSERT_EQ(-1, delete_from_list(pHead, 0));
	ASSERT_EQ(-1, delete_from_list(pHead, -1));
	ASSERT_EQ(0, delete_from_list(pHead, 3));
}


TEST(EmptyList, NormalTest)
{
	linked_list *pHead = (linked_list*)malloc(sizeof(linked_list));

	pHead->next = (linked_list*)malloc(sizeof(linked_list));
	pHead->next->next = (linked_list*)malloc(sizeof(linked_list));
	pHead->next->next->next = (linked_list*)malloc(sizeof(linked_list));
	pHead->next->next->next->next = NULL;


	pHead->next->data = (char *)"layer 1";
	pHead->next->next->data = (char *)"layer 2";
	pHead->next->next->next->data = (char *)"layer 3";

	pHead->next->index = 1;
	pHead->next->next->index = 2;
	pHead->next->next->next->index = 3;


	empty_list(pHead->next->next->next);
	ASSERT_EQ(NULL, pHead->next->next->next->next);

	empty_list(pHead->next->next);
	ASSERT_EQ(NULL, pHead->next->next->next);

	empty_list(pHead->next);
	ASSERT_EQ(NULL, pHead->next->next);

	empty_list(pHead);
	ASSERT_EQ(NULL, pHead->next);
}
