#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int bit_len = 300000;
struct ESL{  //數字struct，一個存分子一個存分母
    bool *h;
    bool *l;
};


bool* bit_gen(float number){
    bool* bit_stream = new bool[bit_len];
    double prob = (number + 1) / 2;
    
    for(int i = 0; i< bit_len;i++){
        
        double r = (double)rand() / (RAND_MAX + 1.0);
        // cout<<r<<endl;
        if(r<prob){
            bit_stream[i] = true;
        }
        else{
            bit_stream[i] = false;
        }
    }
    
    return bit_stream;
}

ESL number_gen(float number, bool *all_one){ //分母先都初始化為一
    ESL output;
    output.h = new bool[bit_len];
    output.l = new bool[bit_len];
    if(number<=1 && number>=-1){
        
    
        // cout<<"generating"<<endl;
        output.h = bit_gen(number);
        output.l = all_one;
    }
    else{
        // cout<<"generating"<<endl;
        output.l = bit_gen(1.0/number);
        output.h = all_one;
    }

    return output;
}



bool* XNOR(bool *a, bool *b){
    bool* XNOR_output = new bool[bit_len];
    // cout<<"I'm fine"<<endl;
    for(int i = 0; i < bit_len; i++){
        if(a[i] == b[i]){
            // cout<<"I'm still fine"<<endl;
            XNOR_output[i] = true;
        }
        else{
            XNOR_output[i] = false;
        }
    }
    return XNOR_output;
}

bool *MUX(bool *a, bool *b){

    bool* MUX_output = new bool[bit_len];
    for(int i = 0; i < bit_len; i++){
        
        double r = (double)rand() / (RAND_MAX + 1.0);
        if(r > 0.5){
            MUX_output[i] = a[i];
        }
        else{
            MUX_output[i] = b[i];
        }
    }
    return MUX_output;
}

ESL ESL_Multiplier(ESL a, ESL b){
    ESL out;
    out.h = new bool[bit_len];
    out.l = new bool[bit_len];
    out.h = XNOR(a.h,b.h);
    out.l = XNOR(a.l,b.l);
    return out;
}

ESL ESL_Adder(ESL a, ESL b){
    ESL out;
    out.h = new bool[bit_len];
    out.l = new bool[bit_len];
    out.h = MUX(XNOR(a.h,b.l),XNOR(a.l,b.h));
    
    out.l = MUX(XNOR(a.l,b.l),bit_gen(0));
    return out;
}

int main(int argc,char** argv){
    srand(time(NULL));
    cout<<"program in"<<endl;
    bool all_one[bit_len];
    for(int i = 0; i< bit_len; i++){
        all_one[i] = true;
    }
    // cout<<"all_one completed"<<endl;
    ESL x,y,out1,out2;
    // cout<<"ESL item completed"<<endl;
    double answer1 = 0,answer2 = 0;
    // x = number_gen(0.005,all_one);//宣告兩個數字
    // y = number_gen(0.04,all_one);
    // cout<<"numnber generated"<<endl;
    // out1 = ESL_Multiplier(x,y);
    // // cout<<"multiplied"<<endl;
    // out2 = ESL_Adder(x,y);
    // cout<<"added"<<endl;

    // for(int i = 0; i< bit_len; i++){
    //     if (out1.h[i] == true){
    //         answer1 += 1;
    //     }
    //     if (out1.l[i] == true){
    //         answer2 += 1;
    //     }
    // }
    // cout<<answer1<<' '<<answer2<<endl;
    // cout<<"x * y = "<<(2*answer1/bit_len - 1)/(2*answer2/bit_len - 1)<<endl;
    // answer1 = 0;
    // answer2 = 0;


    // for(int i = 0; i< bit_len; i++){
    //     if (out2.h[i] == true){
    //         answer1 += 1;
    //     }
    //     if (out2.l[i] == true){
    //         answer2 += 1;
    //     }
    // }
    // cout<<"-----------"<<answer1<<' '<<answer2<<endl;
    // cout<<"x + y = "<<(2*answer1/bit_len - 1)/(2*answer2/bit_len - 1)<<endl;
    // float weight_1[20][4] = {{-0.3650,  0.1136, -0.3621,  0.3817},
    //     {-0.5960,  0.2836,  0.2783,  0.1396},
    //     { 0.0071, -0.3982, -0.3331, -0.3011},
    //     {-0.3889, -0.2968,  0.4992,  0.1149},
    //     {-0.1970, -0.2830,  0.0654,  0.3970},
    //     { 0.5155,  1.3378,  0.3683, -0.0039},
    //     { 0.2016, -0.3183, -0.4295, -0.0404},
    //     {-0.3703, -0.3360,  0.0703, -0.3653},
    //     {-0.1474,  0.0712, -0.4662,  0.3646},
    //     { 0.9291,  0.7635, -0.8991, -0.9186},
    //     {-0.2380, -0.4087,  0.2028,  0.4541},
    //     { 0.3725, -0.2969,  0.8903,  0.5604},
    //     {-0.3627, -0.2265, -0.4729,  0.0596},
    //     { 0.1865, -0.8588,  1.1581,  1.0065},
    //     { 0.1485, -0.9234,  0.9368,  1.3376},
    //     { 0.7792,  0.7996, -0.7694, -0.8574},
    //     { 0.6036,  0.0066,  0.8267,  0.5403},
    //     {-0.0752, -0.4954,  1.2916,  0.9469},
    //     {-0.2143, -0.4795, -0.0692, -0.1084},
    //     { 0.8588,  1.2134, -0.3903, -0.1812}};
    // float bias_1[20] ={0.0974, -0.3697, -0.4755,  0.0691,  0.0978,  1.0600,  0.1753,  0.4838,
    //      0.1439,  0.4877, -0.0996,  0.3071, -0.3572, -1.1438, -0.6967,  0.2753,
    //      0.1332, -0.7853, -0.0566,  0.6732};

    float weight_2[10][4] = {{ 0.9071,  0.5792, -0.8555, -1.3459},
        { 0.0529, -0.0572, -0.3283, -0.3870},
        { 0.6331,  0.4334, -0.7292, -0.8526},
        { 0.2607, -0.7501,  0.9137,  0.5476},
        {-0.4447, -0.0064,  0.3070,  0.3987},
        { 0.3809,  0.3642,  0.0050, -0.6085},
        {-0.2455, -0.4979,  0.3175,  0.2619},
        {-0.3919, -0.2099, -0.4766, -0.1914},
        { 0.2760,  0.1569,  0.2702,  0.3665},
        { 0.2691, -0.3741,  0.4351,  1.2229}};
    float bias_2[10] ={0.9621, -0.4693,  0.6428, -0.0535, -0.3814,  0.5863, -0.4997,  0.0041,
         0.2344, -1.0429};
    float weight_3[3][10] ={{ 0.8500,  0.2360,  1.0325, -0.8390,  0.0752,  0.3487, -0.0996,  0.0241,
         -0.0773, -0.5459},
        { 0.5328,  0.1500,  0.5266,  0.4966, -0.2748,  0.0447,  0.1743, -0.2811,
          0.1686, -0.0506},
        {-0.8802,  0.3087, -1.1884,  0.8887,  0.0599, -0.2744,  0.3841,  0.2849,
          0.1093,  1.0187}};
    float bias_3[3] = {0.3917, -0.0422, -0.5115};

    float x_test[30][4] = {{6.1000, 2.8000, 4.7000, 1.2000},
        {5.7000, 3.8000, 1.7000, 0.3000},
        {7.7000, 2.6000, 6.9000, 2.3000},
        {6.0000, 2.9000, 4.5000, 1.5000},
        {6.8000, 2.8000, 4.8000, 1.4000},
        {5.4000, 3.4000, 1.5000, 0.4000},
        {5.6000, 2.9000, 3.6000, 1.3000},
        {6.9000, 3.1000, 5.1000, 2.3000},
        {6.2000, 2.2000, 4.5000, 1.5000},
        {5.8000, 2.7000, 3.9000, 1.2000},
        {6.5000, 3.2000, 5.1000, 2.0000},
        {4.8000, 3.0000, 1.4000, 0.1000},
        {5.5000, 3.5000, 1.3000, 0.2000},
        {4.9000, 3.1000, 1.5000, 0.1000},
        {5.1000, 3.8000, 1.5000, 0.3000},
        {6.3000, 3.3000, 4.7000, 1.6000},
        {6.5000, 3.0000, 5.8000, 2.2000},
        {5.6000, 2.5000, 3.9000, 1.1000},
        {5.7000, 2.8000, 4.5000, 1.3000},
        {6.4000, 2.8000, 5.6000, 2.2000},
        {4.7000, 3.2000, 1.6000, 0.2000},
        {6.1000, 3.0000, 4.9000, 1.8000},
        {5.0000, 3.4000, 1.6000, 0.4000},
        {6.4000, 2.8000, 5.6000, 2.1000},
        {7.9000, 3.8000, 6.4000, 2.0000},
        {6.7000, 3.0000, 5.2000, 2.3000},
        {6.7000, 2.5000, 5.8000, 1.8000},
        {6.8000, 3.2000, 5.9000, 2.3000},
        {4.8000, 3.0000, 1.4000, 0.3000},
        {4.8000, 3.1000, 1.6000, 0.2000}};
    float corr_answer[30] = {1, 0, 2, 1, 1, 0, 1, 2, 1, 1, 2, 0, 0, 0, 0, 1, 2, 1, 1, 2, 0, 2, 0, 2,
        2, 2, 2, 2, 0, 0};
    ESL layer_0[4];
    // ESL layer_1[20];
    ESL layer_2[10];
    ESL layer_3[3];
    float corr_count = 0;
    float max=0,temp=0,max_cand=0;
    for(int k=0;k<30;k++){
        for(int i=0;i<4;i++){
            layer_0[i] = number_gen(x_test[k][i],all_one);
            // answer1 = 0;
            // answer2 = 0;
            // for(int j = 0; j< bit_len; j++){
            //     if (layer_0[i].h[j] == true){
            //         answer1 += 1;
            //     }
            //     if (layer_0[i].l[j] == true){
            //         answer2 += 1;
            //     }
            // }
            // temp = (2*answer1/bit_len - 1)/(2*answer2/bit_len - 1);
            // cout<<x_test[k][i]<<' '<<temp<<endl;
        }
            
        // for(int i=0;i<20;i++){
        //     layer_1[i] = number_gen(0,all_one);
        // }
        for(int i=0;i<10;i++){
            layer_2[i] = number_gen(0,all_one);
        }
        for(int i=0;i<3;i++){
            layer_3[i] = number_gen(0,all_one);
        }

        // for(int i=0;i<20;i++){
        //     for(int j=0;j<4;j++){
        //         layer_1[i] = ESL_Adder(layer_1[i] ,ESL_Multiplier(layer_0[j],number_gen(weight_1[i][j],all_one)));
        //     }
        //     ESL_Adder(layer_1[i],number_gen(bias_1[i],all_one));
        // }

        for(int i=0;i<10;i++){
            for(int j=0;j<4;j++){
                layer_2[i] = ESL_Adder(layer_2[i] ,ESL_Multiplier(layer_0[j],number_gen(weight_2[i][j],all_one)));
            }
            ESL_Adder(layer_2[i],number_gen(bias_2[i],all_one));
            
        }
        
        for(int i=0;i<3;i++){
            for(int j=0;j<10;j++){
                layer_3[i] = ESL_Adder(layer_3[i] ,ESL_Multiplier(layer_2[j],number_gen(weight_3[i][j],all_one)));
            }
            ESL_Adder(layer_3[i],number_gen(bias_3[i],all_one));
        }
        
        for(int j=0;j<3;j++){
            answer1 = 0;
            answer2 = 0;
            for(int i = 0; i< bit_len; i++){
                if (layer_3[j].h[i] == true){
                    answer1 += 1;
                }
                if (layer_3[j].l[i] == true){
                    answer2 += 1;
                }
            }
            temp = (2*answer1/bit_len - 1)/(2*answer2/bit_len - 1);
            cout<<temp<<endl;
            if(j==0){
                max = temp;
                max_cand = 0;
            }
            else{
                if(temp > max){
                    max = temp;
                    max_cand = j;
                }
            }

        }
        cout<<max_cand<<endl;
        if(max_cand == corr_answer[k]){
            corr_count += 1;
            cout<<"correct!!!!!("<<corr_count<<'/'<<k+1<<')'<<endl;
        }
        else{
            cout<<"wrong!!!!!("<<corr_count<<'/'<<k+1<<')'<<endl;
        }

    }
    
    cout<<"The rate of correctness is: "<<corr_count/30.0<<endl;
    return 0;
}