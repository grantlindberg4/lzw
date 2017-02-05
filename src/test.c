#include <stdio.h>
#include <assert.h>

#include "seq.h"
#include "dict.h"

void test_seq() {
	Sequence* empty = create_sequence();
	assert(empty->length == 0);
	assert(empty->chars[0] == '\0');
	delete_sequence(empty);

	Sequence* abcd = create_sequence();
	append(abcd, 'a');
	assert(abcd->length == 1);
	assert(abcd->chars[0] == 'a');
	assert(abcd->chars[1] == '\0');
	append(abcd, 'b');
	assert(abcd->length == 2);
	assert(abcd->chars[0] == 'a');
	assert(abcd->chars[1] == 'b');
	assert(abcd->chars[2] == '\0');
	append(abcd, 'c');
	assert(abcd->length == 3);
	assert(abcd->chars[0] == 'a');
	assert(abcd->chars[1] == 'b');
	assert(abcd->chars[2] == 'c');
	assert(abcd->chars[3] == '\0');
	append(abcd, '\0');
	assert(abcd->length == 4);
	assert(abcd->chars[0] == 'a');
	assert(abcd->chars[1] == 'b');
	assert(abcd->chars[2] == 'c');
	assert(abcd->chars[3] == '\0');
	assert(abcd->chars[4] == '\0');
	append(abcd, 'd');
	assert(abcd->length == 5);
	assert(abcd->chars[0] == 'a');
	assert(abcd->chars[1] == 'b');
	assert(abcd->chars[2] == 'c');
	assert(abcd->chars[3] == '\0');
	assert(abcd->chars[4] == 'd');
	assert(abcd->chars[5] == '\0');
	delete_sequence(abcd);

	Sequence* ac_1 = create_sequence();
	append(ac_1, 'a');
	append(ac_1, '\0');
	append(ac_1, 'c');
	Sequence* ac_2 = create_sequence();
	append(ac_2, 'a');
	append(ac_2, '\0');
	append(ac_2, 'c');
	Sequence* ace = create_sequence();
	append(ace, 'a');
	append(ace, '\0');
	append(ace, 'c');
	append(ace, 'e');
	assert(sequences_are_equal(ac_1, ac_1));
	assert(sequences_are_equal(ac_1, ac_2));
	assert(!sequences_are_equal(ac_1, ace));
	assert(sequences_are_equal(ac_2, ac_1));
	assert(sequences_are_equal(ac_2, ac_2));
	assert(!sequences_are_equal(ac_2, ace));
	assert(!sequences_are_equal(ace, ac_1));
	assert(!sequences_are_equal(ace, ac_2));
	assert(sequences_are_equal(ace, ace));
	delete_sequence(ac_1);
	delete_sequence(ac_2);
	delete_sequence(ace);

	Sequence* ac = create_sequence();
	append(ac, 'a');
	append(ac, '\0');
	append(ac, 'c');
	Sequence* ac_copy = copy_sequence(ac);
	assert(ac != ac_copy);
	assert(sequences_are_equal(ac, ac_copy));
	delete_sequence(ac);
	delete_sequence(ac_copy);

	Sequence* ac_3 = create_sequence();
	append(ac_3, 'a');
	append(ac_3, '\0');
	append(ac_3, 'c');
	Sequence* ac_4 = copy_sequence(ac_3);
	Sequence* bc = create_sequence();
	append(bc, 'b');
	append(bc, 'c');
	assert(compute_hash_val(ac_3) == compute_hash_val(ac_3));
	assert(compute_hash_val(ac_3) == compute_hash_val(ac_4));
	assert(compute_hash_val(ac_3) != compute_hash_val(bc));
	delete_sequence(ac_3);
	delete_sequence(ac_4);
	delete_sequence(bc);
}

void test_dict() {
	unsigned int code = 0xDEADBEEF;
	Dict* dict_1 = create_dictionary();
	Sequence* empty = create_sequence();
	Sequence* a = create_sequence();
	append(a, 'a');
	Sequence* foo = create_sequence();
	append(foo, 'f');
	append(foo, 'o');
	append(foo, 'o');
	assert(!search_for_key(dict_1, empty, &code));
	assert(!search_for_key(dict_1, a, &code));
	assert(!search_for_key(dict_1, foo, &code));
	assert(code == 0xDEADBEEF);

	insert_to_dictionary(dict_1, copy_sequence(empty), 0xAB);
	assert(search_for_key(dict_1, empty, &code));
	assert(code == 0xAB);
	assert(!search_for_key(dict_1, a, &code));
	assert(!search_for_key(dict_1, foo, &code));

	insert_to_dictionary(dict_1, copy_sequence(a), 0xCD);
	assert(search_for_key(dict_1, empty, &code));
	assert(code == 0xAB);
	assert(search_for_key(dict_1, a, &code));
	assert(code == 0xCD);
	assert(!search_for_key(dict_1, foo, &code));

	insert_to_dictionary(dict_1, copy_sequence(foo), 0xEF);
	assert(search_for_key(dict_1, empty, &code));
	assert(code == 0xAB);
	assert(search_for_key(dict_1, a, &code));
	assert(code == 0xCD);
	assert(search_for_key(dict_1, foo, &code));
	assert(code == 0xEF);

	destroy_dictionary(dict_1);

	Dict* dict_2 = initialize_dictionary();

	assert(!search_for_key(dict_2, empty, &code));
	assert(search_for_key(dict_2, a, &code));
	assert(code == 'a');
	assert(!search_for_key(dict_2, foo, &code));

	insert_to_dictionary(dict_2, copy_sequence(empty), 0xAB);
	assert(search_for_key(dict_2, empty, &code));
	assert(code == 0xAB);
	assert(search_for_key(dict_2, a, &code));
	assert(code == 'a');
	assert(!search_for_key(dict_2, foo, &code));

	insert_to_dictionary(dict_2, copy_sequence(foo), 0xEF);
	assert(search_for_key(dict_2, empty, &code));
	assert(code == 0xAB);
	assert(search_for_key(dict_2, a, &code));
	assert(code == 'a');
	assert(search_for_key(dict_2, foo, &code));
	assert(code == 0xEF);

	destroy_dictionary(dict_2);

	delete_sequence(empty);
	delete_sequence(a);
	delete_sequence(foo);
}

int main() {
	test_seq();
	test_dict();
	printf("All tests passed!\n");
	return 0;
}
