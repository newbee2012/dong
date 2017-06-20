#include <iostream>
#include "util/gen_bmp.hpp"
#include "input_layer.hpp"
#include "conv_layer.hpp"
#include "pool_layer.hpp"
#include "full_connect_layer.hpp"
#include "relu_layer.hpp"
#include "softmax_layer.hpp"
#include "util/db.hpp"

#include <boost/shared_ptr.hpp>
using namespace std;
using namespace caffe;
using namespace dong;

int sum = 0;
void test2(char* p, char* q, int count1, int count2, int v)
{
    if (count1 + count2 == 0) {
        cout << p << endl;
        sum++;
        return;
    }

    if (v >= 0 && count1 > 0) {
        *q = '(';
        test2(p, q + 1, count1 - 1, count2, v + 1);
    }

    if (count2 > 0) {
        *q = ')';
        test2(p, q + 1, count1, count2 - 1, v - 1);
    }
}

void train()
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
        boost::shared_ptr<Neuron[]> inputImage(new Neuron[height * width]());

        for (int c = 0; c < channels; c++) {
            for (int w = 0; w < width; w++) {
                for (int h = 0; h < height; h++) {
                    inputImage[w * height + h]._value = (BYTE)(datum.data()[w * height + h]); //!= 0 ? 1 : 0;
                }
            }
        }

        boost::shared_ptr<Data> inputData((new Data(1, channels, height, width))->setUp(inputImage));
        //L1.inputLayer
        boost::shared_ptr<InputLayer> inputLayer(new InputLayer());
        inputLayer->setUp(inputData);
        cout << "Label: " << label << endl;
        inputLayer->forward();
        //L2.convLayer1
        boost::shared_ptr<ConvLayer> convLayer1(new ConvLayer());
        convLayer1->init(1, 1, 5, 5);
        convLayer1->setUp(inputLayer->getTopData());
        convLayer1->forward();
        //L3.poolLayer
        boost::shared_ptr<PoolLayer> poolLayer1(new PoolLayer());
        poolLayer1->init(2, 2, 2, 2);
        poolLayer1->setUp(convLayer1->getTopData());
        poolLayer1->forward();
        //L4.convLayer
        boost::shared_ptr<ConvLayer> convLayer2(new ConvLayer());
        convLayer2->init(1, 1, 5, 5);
        convLayer2->setUp(poolLayer1->getTopData());
        convLayer2->forward();
        //L5.poolLayer
        boost::shared_ptr<PoolLayer> poolLayer2(new PoolLayer());
        poolLayer2->init(2, 2, 2, 2);
        poolLayer2->setUp(convLayer2->getTopData());
        poolLayer2->forward();
        //L6.FullConnectLayer
        boost::shared_ptr<FullConnectLayer> fullConnectLayer(new FullConnectLayer());
        fullConnectLayer->init(10);
        fullConnectLayer->setUp(poolLayer2->getTopData());
        fullConnectLayer->forward();
        //L7.reluLayer
        boost::shared_ptr<ReluLayer> reluLayer(new ReluLayer());
        reluLayer->init();
        reluLayer->setUp(fullConnectLayer->getTopData());
        reluLayer->forward();
        //L8.FullConnectLayer
        boost::shared_ptr<FullConnectLayer> fullConnectLayer2(new FullConnectLayer());
        fullConnectLayer2->init(10);
        fullConnectLayer2->setUp(reluLayer->getTopData());
        fullConnectLayer2->forward();
        //L9.SoftmaxLayer
        boost::shared_ptr<SoftmaxLayer> softmaxLayer(new SoftmaxLayer());
        softmaxLayer->init();
        softmaxLayer->setUp(fullConnectLayer2->getTopData());
        softmaxLayer->forward();
        //print per layer
        cout << "---------inputLayer top_data-----------" << endl;
        inputLayer->getTopData()->print();
        char filename[32];
        const char* format = "inputLayer_top_data_l%d_%d.bmp";
        snprintf(filename, sizeof(filename), format, label, i);
        inputLayer->getTopData()->genBmp(filename);

        cout << "---------convLayer1 weight-----------" << endl;
        convLayer1->getWeightData()->print();
        convLayer1->getWeightData()->genBmp("convLayer1_weight_data.bmp");

        cout << "---------convLayer1 top_data-----------" << endl;
        convLayer1->getTopData()->print();
        convLayer1->getTopData()->genBmp("convLayer1_top_data.bmp");

        cout << "---------poolLayer1 weight-----------" << endl;
        poolLayer1->getWeightData()->print();
        poolLayer1->getWeightData()->genBmp("poolLayer1_weight_data.bmp");

        cout << "---------poolLayer1 top_data-----------" << endl;
        poolLayer1->getTopData()->print();
        poolLayer1->getTopData()->genBmp("poolLayer1_top_data.bmp");

        cout << "---------convLayer2 weight-----------" << endl;
        convLayer2->getWeightData()->print();
        convLayer2->getWeightData()->genBmp("convLayer2_weight_data.bmp");

        cout << "---------convLayer2 top_data-----------" << endl;
        convLayer2->getTopData()->print();
        convLayer2->getTopData()->genBmp("convLayer2_top_data.bmp");

        cout << "---------poolLayer2 weight-----------" << endl;
        poolLayer2->getWeightData()->print();
        poolLayer2->getWeightData()->genBmp("poolLayer2_weight_data.bmp");

        cout << "---------poolLayer2 top_data-----------" << endl;
        poolLayer2->getTopData()->print();
        poolLayer2->getTopData()->genBmp("poolLayer2_top_data.bmp");

        cout << "---------fullConnectLayer weight_data-----------" << endl;
        fullConnectLayer->getWeightData()->print();

        cout << "---------fullConnectLayer top_data-----------" << endl;
        fullConnectLayer->getTopData()->print();

        cout << "---------reluLayer weight-----------" << endl;
        reluLayer->getWeightData()->print();
        reluLayer->getWeightData()->genBmp("reluLayer_weight_data.bmp");

        cout << "---------reluLayer top_data-----------" << endl;
        reluLayer->getTopData()->print();
        reluLayer->getTopData()->genBmp("reluLayer_top_data.bmp");

        cout << "---------fullConnectLayer2 weight_data-----------" << endl;
        fullConnectLayer2->getWeightData()->print();

        cout << "---------fullConnectLayer2 top_data-----------" << endl;
        fullConnectLayer2->getTopData()->print();

        cout << "---------softmaxLayer top_data-----------" << endl;
        softmaxLayer->getTopData()->print();
        corsor->Next();
    }

    delete corsor;
    mydb->Close();
    delete mydb;
}
int main()
{
    train();
    cout << "Hello world!" << endl;
    return 0;
}
