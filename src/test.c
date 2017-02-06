#include <stdio.h>
#include <assert.h>
#include <dirent.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "seq.h"
#include "dict.h"
#include "lzw.h"
#include "table.h"

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



	Dict* dict_3 = initialize_dictionary();

	Sequence* one = create_sequence();
	append(one, '\1');

	Sequence* zero_one = create_sequence();
	append(zero_one, '\0');
	append(zero_one, '\1');

	unsigned int zero_one_code = NUM_CHARS;

	assert(search_for_key(dict_3, one, &code));
	assert(code == '\1');
	assert(!search_for_key(dict_3, zero_one, &code));

	insert_to_dictionary(dict_3, copy_sequence(zero_one), zero_one_code);

	assert(search_for_key(dict_3, zero_one, &code));
	assert(code == zero_one_code);
	assert(search_for_key(dict_3, one, &code));
	assert(code == '\1');
}

void test_table() {
	Sequence* empty = create_sequence();
	Sequence* a = create_sequence();
	append(a, 'a');
	Sequence* foo = create_sequence();
	append(foo, 'f');
	append(foo, 'o');
	append(foo, 'o');

	unsigned empty_code = NUM_CHARS;
	unsigned a_code = 'a';
	unsigned foo_code = NUM_CHARS+1;

	Table* table_1 = create_table();

	assert(table_1->array[empty_code] == NULL);
	assert(table_1->array[a_code] == NULL);
	assert(table_1->array[foo_code] == NULL);

	table_1->array[empty_code] = empty;
	table_1->array[a_code] = a;
	table_1->array[foo_code] = foo;

	destroy_table(table_1);



	empty = create_sequence();
	a = create_sequence();
	append(a, 'a');
	foo = create_sequence();
	append(foo, 'f');
	append(foo, 'o');
	append(foo, 'o');

	Table* table_2 = initialize_table();

	assert(table_2->array[empty_code] == NULL);
	assert(sequences_are_equal(table_2->array[a_code], a));
	assert(table_2->array[foo_code] == NULL);

	table_2->array[empty_code] = empty;
	table_2->array[foo_code] = foo;

	delete_sequence(a);
	destroy_table(table_2);
}

bool ext_equals(struct dirent* entry, const char* extension) {
	int name_len = strlen(entry->d_name);
	int ext_len = strlen(extension);
	if(name_len < ext_len) {
		return false;
	}
	const char* file_ext = entry->d_name + name_len - ext_len;

	return strcmp(file_ext, extension) == 0;
}

bool files_are_equal(FILE* a, FILE* b) {
	Sequence* seq_a = create_sequence();
	Sequence* seq_b = create_sequence();

	int byte;
	while(true) {
		byte = fgetc(a);
		if(byte == EOF) {
			break;
		}
		append(seq_a, byte);
	}
	while(true) {
		byte = fgetc(b);
		if(byte == EOF) {
			break;
		}
		append(seq_b, byte);
	}
	bool equal = sequences_are_equal(seq_a, seq_b);
	delete_sequence(seq_a);
	delete_sequence(seq_b);
	return equal;
}

typedef void(*DoFixture)(char* raw_name, char* lzw_name);

void for_each_fixture(DoFixture f) {
	DIR* fixtures_dir = opendir("./fixtures");
	assert(fixtures_dir != NULL);

	struct dirent* entry;
	while(true) {
		entry = readdir(fixtures_dir);
		if(entry == NULL) {
			break;
		}

		if(ext_equals(entry, ".bin")) {
			const char* entry_name = entry->d_name;
			int raw_name_length = 0;
			raw_name_length += sizeof("./fixtures/");
			raw_name_length += strlen(entry_name);
			int lzw_name_length = raw_name_length + sizeof(".lzw");
			char* raw_name = malloc(raw_name_length);
			snprintf(raw_name, raw_name_length, "./fixtures/%s", entry_name);

			char* lzw_name = malloc(lzw_name_length);
			snprintf(lzw_name, lzw_name_length, "./fixtures/%s.lzw", entry_name);

			f(raw_name, lzw_name);
			free(raw_name);
			free(lzw_name);
		}
	}

	closedir(fixtures_dir);
}

void test_lzw_encode(char* raw_name, char* lzw_name) {
	FILE* raw = fopen(raw_name, "r");
	assert(raw != NULL);
	FILE* lzw_expected = fopen(lzw_name, "r");
	assert(lzw_expected != NULL);
	FILE* lzw_actual = tmpfile();
	assert(lzw_actual != NULL);
	printf("Comparing encoding %s and %s\n", raw_name, lzw_name);

	encode(raw, lzw_actual);

	fseek(lzw_actual, 0, SEEK_SET);

	bool equal = files_are_equal(lzw_expected, lzw_actual);

	fclose(raw);
	fclose(lzw_expected);
	fclose(lzw_actual);

	assert(equal);
}

void test_lzw_decode(char* raw_name, char* lzw_name) {
	FILE* raw_expected = fopen(raw_name, "r");
	assert(raw_expected != NULL);
	FILE* lzw = fopen(lzw_name, "r");
	assert(lzw != NULL);
	FILE* raw_actual = tmpfile();
	assert(raw_actual != NULL);
	printf("Comparing decoding %s and %s\n", lzw_name, raw_name);

	decode(lzw, raw_actual);

	fseek(raw_actual, 0, SEEK_SET);

	bool equal = files_are_equal(raw_expected, raw_actual);

	fclose(raw_expected);
	fclose(lzw);
	fclose(raw_actual);

	assert(equal);
}

void test_lzw() {
	for_each_fixture(test_lzw_encode);
	for_each_fixture(test_lzw_decode);
}

int main() {
	test_seq();
	test_dict();
	test_table();
	test_lzw();
	printf("All tests passed!\n");
	return 0;
}
