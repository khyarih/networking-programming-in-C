#include<rpc/rpc.h>
#include<rpc/xdr.h>
#include<rpc/types.h>
#include<stdio.h>
#include<stdlib.h>

struct type{
    int int_data;
    float float_data;
    char char_data;
};

bool_t xdr_type(XDR* xdr_ptr, struct type* data){

    return (
        xdr_int(xdr_ptr,&data->int_data)
        && xdr_float(xdr_ptr, &data->float_data)
        && xdr_char(xdr_ptr, &data->char_data)
    );

}

int main(){
    //TODO:

    return 0;
}