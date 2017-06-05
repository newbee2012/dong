#include <iostream>
#include "input_layer.hpp"
#include "util/db.hpp"
#include <boost/shared_ptr.hpp>
using namespace std;
using namespace caffe;
using namespace dong;

int main()
{
    db::DB* mydb = db::GetDB("lmdb");
    mydb->Open("/home/chendejia/workspace/github/dong/data/mnist_train_lmdb", db::READ);
    db::Cursor* corsor = mydb->NewCursor();
    corsor->SeekToFirst();

    for (int i = 0; i < 2 && corsor->valid(); i++)
    {
        const string& value = corsor->value();

        Datum datum;
        datum.ParseFromString(value);
        int channels = datum.channels();
        int width = datum.width();
        int height = datum.height();
        int label = datum.label();

        boost::shared_ptr<int> inputImage(new int[width*height]);
        int* p = inputImage.get();
        for (int c = 0; c < channels; c++)
        {
            for (int w = 0; w < width; w++)
            {
                for (int h = 0; h < height; h++)
                {
                    *(p++)= (int)(datum.data()[w * height + h]);
                }
            }
        }

        boost::shared_ptr<Data> inputData((new Data(1, channels, width, height, false))->setUp(inputImage));
        boost::shared_ptr<InputLayer> inputLayer(new InputLayer());
        inputLayer->setUp(inputData);
        cout<<"Label: "<<label<<endl;
        inputLayer->forward();


        inputLayer->getTopData()->print();
        corsor->Next();
    }

    delete corsor;
    mydb->Close();
    delete mydb;
    cout << "Hello world!" << endl;
    return 0;
}
