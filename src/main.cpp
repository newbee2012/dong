#include <iostream>
#include "input_layer.hpp"
#include "conv_layer.hpp"
#include "util/db.hpp"
#include <boost/shared_ptr.hpp>
using namespace std;
using namespace caffe;
using namespace dong;

int main()
{
    srand((int)time(0));
    db::DB* mydb = db::GetDB("lmdb");
    mydb->Open("/home/chendejia/workspace/github/dong/data/mnist_train_lmdb", db::READ);
    db::Cursor* corsor = mydb->NewCursor();
    corsor->SeekToFirst();

    for (int i = 0; i < 1 && corsor->valid(); i++) {
        const string& value = corsor->value();
        Datum datum;
        datum.ParseFromString(value);
        int channels = datum.channels();
        int width = datum.width();
        int height = datum.height();
        int label = datum.label();
        boost::shared_ptr<int> inputImage(new int[width * height]);
        int* p = inputImage.get();

        for (int c = 0; c < channels; c++) {
            for (int w = 0; w < width; w++) {
                for (int h = 0; h < height; h++) {
                    *(p++) = (int)(datum.data()[w * height + h])!=0 ?1:0;
                }
            }
        }

        boost::shared_ptr<Data> inputData((new Data(1, channels, height, width, false))->setUp(inputImage));

        //L1.inputLayer
        boost::shared_ptr<InputLayer> inputLayer(new InputLayer());
        inputLayer->setUp(inputData);
        cout << "Label: " << label << endl;
        inputLayer->forward();

        //L2.convLayer
        boost::shared_ptr<ConvLayer> convLayer(new ConvLayer());
        convLayer->init(1, 1, 5, 5);
        convLayer->setUp(inputLayer->getTopData());
        convLayer->forward();

        //print per layer
        inputLayer->getTopData()->print();
        convLayer->getTopData()->print();
        corsor->Next();
    }

    delete corsor;
    mydb->Close();
    delete mydb;
    cout << "Hello world!" << endl;
    return 0;
}
