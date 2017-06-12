#include <iostream>
#include "util/gen_bmp.hpp"
#include "input_layer.hpp"
#include "conv_layer.hpp"
#include "pool_layer.hpp"
#include "inner_product_layer.hpp"
#include "relu_layer.hpp"
#include "softmax_layer.hpp"
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
        boost::shared_ptr<Neuron<float> > inputImage(new Neuron<float>[width * height]);
        Neuron<float>* p = inputImage.get();

        for (int c = 0; c < channels; c++) {
            for (int w = 0; w < width; w++) {
                for (int h = 0; h < height; h++) {
                    (p++)->value = (BYTE)(datum.data()[w * height + h]); //!= 0 ? 1 : 0;
                }
            }
        }

        boost::shared_ptr<Data> inputData((new Data(1, channels, height, width, false))->setUp(inputImage));
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

        //L6.InnerProductLayer
        boost::shared_ptr<InnerProductLayer> innerProductLayer(new InnerProductLayer());
        innerProductLayer->init(10);
        innerProductLayer->setUp(poolLayer2->getTopData());
        innerProductLayer->forward();

        //L7.reluLayer
        boost::shared_ptr<ReluLayer> reluLayer(new ReluLayer());
        reluLayer->init();
        reluLayer->setUp(innerProductLayer->getTopData());
        reluLayer->forward();

        //L8.InnerProductLayer
        boost::shared_ptr<InnerProductLayer> innerProductLayer2(new InnerProductLayer());
        innerProductLayer2->init(10);
        innerProductLayer2->setUp(reluLayer->getTopData());
        innerProductLayer2->forward();

        //L9.SoftmaxLayer
        boost::shared_ptr<SoftmaxLayer> softmaxLayer(new SoftmaxLayer());
        softmaxLayer->init();
        softmaxLayer->setUp(innerProductLayer2->getTopData());
        softmaxLayer->forward();

/*
        //print per layer
        cout<<"---------inputLayer top_data-----------"<<endl;
        inputLayer->getTopData()->print();

        char filename[32];
        const char* format = "inputLayer_top_data_l%d_%d.bmp";
        sprintf(filename,format,label, i);
        inputLayer->getTopData()->genBmp(filename);

        cout<<"---------convLayer1 top_data-----------"<<endl;
        convLayer1->getTopData()->print();
        convLayer1->getTopData()->genBmp("convLayer1_top_data.bmp");

        cout<<"---------convLayer1 weight-----------"<<endl;
        convLayer1->getWeightData()->print();
        convLayer1->getWeightData()->genBmp("convLayer1_weight_data.bmp");

        cout<<"---------poolLayer1 top_data-----------"<<endl;
        poolLayer1->getTopData()->print();
        poolLayer1->getTopData()->genBmp("poolLayer1_top_data.bmp");

        //cout<<"---------convLayer2 bottom_data-----------"<<endl;
        //convLayer2->getBottomData()->print();
        cout<<"---------convLayer2 top_data-----------"<<endl;
        convLayer2->getTopData()->print();
        convLayer2->getTopData()->genBmp("convLayer2_top_data.bmp");

        cout<<"---------convLayer2 weight-----------"<<endl;
        convLayer2->getWeightData()->print();
        convLayer2->getWeightData()->genBmp("convLayer2_weight_data.bmp");

        cout<<"---------poolLayer2 top_data-----------"<<endl;
        poolLayer2->getTopData()->print();
        poolLayer2->getTopData()->genBmp("poolLayer2_top_data.bmp");

        cout<<"---------innerProductLayer weight_data-----------"<<endl;
        innerProductLayer->getWeightData()->print();
        cout<<"---------innerProductLayer top_data-----------"<<endl;
        innerProductLayer->getTopData()->print();

        cout<<"---------reluLayer top_data-----------"<<endl;
        reluLayer->getTopData()->print();
        reluLayer->getTopData()->genBmp("reluLayer_top_data.bmp");

        cout<<"---------innerProductLayer2 weight_data-----------"<<endl;
        innerProductLayer2->getWeightData()->print();
        cout<<"---------innerProductLayer2 top_data-----------"<<endl;
        innerProductLayer2->getTopData()->print();

        cout<<"---------softmaxLayer weight_data-----------"<<endl;
        softmaxLayer->getWeightData()->print();
        cout<<"---------softmaxLayer top_data-----------"<<endl;
        softmaxLayer->getTopData()->print();
*/
        corsor->Next();
    }

    delete corsor;
    mydb->Close();
    delete mydb;


    cout << "Hello world!" << endl;
    return 0;
}
