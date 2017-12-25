#include <stdio.h>

struct DBF_HEADER {
    struct {
            char version : 3;
            bool memo_exist : 1;
            char sql_table_reserved : 1;
            char sql_table_flags : 2;
            bool dbt_exist : 1;
    } signature;
    struct {
        char YY;
        char MM;
        char DD;
    } last_modified_date;
    int number_of_record;
    short header_lenght;
    short record_length;
    short reserved;
    bool incompleate_transaction_flag;
    bool encryption_flag;
    int multiuser[3];
    bool mdx_flag;
    char code_page_id;
    short reserved2;
};
int main(void) {
    void* a = new DBF_HEADER;
    DBF_HEADER *b;
    b = static_cast<DBF_HEADER *>(a);
    FILE* file;
    printf("Size b is: %li\n", sizeof(*b));
    const char *fname = "OKEI.DBF";
    file = fopen(fname,"r");
    fgets((char*)a,sizeof(a),file);
    fclose(file);
    const char *format = ""
            "version = %x;\n"
            "memo_exist = %x;\n"
            "sql_table_reserved = %x;\n"
            "sql_table_flags = %x;\n"
            "dbt_exist = %x;\n"
            "\n"
            "YY = %i;\n"
            "MM = %i;\n"
            "DD = %i;\n"
            "\n"
            "number_of_record = %i;\n"
            "header_lenght = %i;\n"
            "record_length = %i;\n"
            "reserved = %x;\n"
            "incompleate_transaction_flag = %x;\n"
            "encryption_flag = %x;\n"
            "mdx_flag = %x;\n"
            "code_page_id = %x;\n"
            "resserved2 = %x;\n";
    printf(format,
           b->signature.version,
           b->signature.memo_exist,
           b->signature.sql_table_reserved,
           b->signature.sql_table_flags,
           b->signature.dbt_exist,
           b->last_modified_date.YY,
           b->last_modified_date.MM,
           b->last_modified_date.DD,
           b->number_of_record,
           b->header_lenght,
           b->record_length,
           b->reserved,
           b->incompleate_transaction_flag,
           b->encryption_flag,
           b->mdx_flag,
           b->code_page_id,
           b->reserved2
    );
    return 0;
}