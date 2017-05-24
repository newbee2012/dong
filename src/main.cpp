#include <iostream>
#include "data_layer.hpp"
#include "util/db.hpp"
using namespace std;
using namespace caffe;

int main()
{
    db::DB* mydb = db::GetDB("lmdb");
    mydb->Open("../../data/mnist_train_lmdb",db::READ);
    db::Cursor* corsor =mydb->NewCursor();
    corsor->SeekToFirst();
    Datum datum;
    for(int i = 0;i<2 && corsor->valid();i++)
    {
        const string& value = corsor->value();
        datum.ParseFromString(value);
        int wight =datum.width();
        int height = datum.height();
        cout<<"image"<<corsor->key()<<",label is "<<datum.label()<<endl;
        for(int w=0; w<wight; w++)
        {
            for(int h=0; h<height; h++)
            {
                char x = (int)(datum.data()[w*height+h])!=0 ? '#':'.';
                cout<<x;
                cout<<" ";
            }

            cout<<endl;
        }

        corsor->Next();
    }


    cout << "Hello world!" << endl;
    return 0;
}
