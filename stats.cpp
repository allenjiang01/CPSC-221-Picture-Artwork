
#include "stats.h"

stats::stats(PNG & im){
    //cout <<"stats";

for (int i = 0; i < (int)im.width(); i++) {
    
        vector<long> sum_r;
        vector<long> sum_g;
        vector<long> sum_b;
        vector<long> sum_sq_r;
        vector<long> sum_sq_g;
        vector<long> sum_sq_b;


        for (int j = 0; j < (int)im.height(); j++) {

            RGBAPixel *p = im.getPixel(i, j);
            long r = p->r;
            long g = p->g;
            long b = p->b;
            long sr = r*r;
            long sg = g*g;
            long sb = b*b;

            if (i==0 && j==0)  {
                sum_r.push_back(r);  
                sum_g.push_back(g);  
                sum_b.push_back(b);  
                sum_sq_r.push_back(sr);  
                sum_sq_g.push_back(sg);  
                sum_sq_b.push_back(sb);  
            } else if (i==0) {
                sum_r.push_back(r + sum_r[j-1]);
                sum_g.push_back(g + sum_g[j-1]);
                sum_b.push_back(b + sum_b[j-1]);
                sum_sq_r.push_back(sr + sum_sq_r[j-1]);
                sum_sq_g.push_back(sg + sum_sq_g[j-1]);
                sum_sq_b.push_back(sb + sum_sq_b[j-1]);
            } else if (j==0) {
                sum_r.push_back(r + sumRed[i-1][0]);
                sum_g.push_back(g + sumGreen[i-1][0]);
                sum_b.push_back(b + sumBlue[i-1][0]);
                sum_sq_r.push_back(sr + sumsqRed[i-1][0]);
                sum_sq_g.push_back(sg + sumsqGreen[i-1][0]);
                sum_sq_b.push_back(sb + sumsqBlue[i-1][0]);
            } else {
                sum_r.push_back(r + sumRed[i-1][j] - sumRed[i-1][j-1] + sum_r[j-1]);
                sum_g.push_back(g + sumGreen[i-1][j] - sumGreen[i-1][j-1] + sum_g[j-1]);
                sum_b.push_back(b + sumBlue[i-1][j] - sumBlue[i-1][j-1] + sum_b[j-1]);
                sum_sq_r.push_back(sr + sumsqRed[i-1][j] - sumsqRed[i-1][j-1] + sum_sq_r[j-1]);
                sum_sq_g.push_back(sg + sumsqGreen[i-1][j] - sumsqGreen[i-1][j-1] + sum_sq_g[j-1]);
                sum_sq_b.push_back(sb + sumsqBlue[i-1][j] - sumsqBlue[i-1][j-1] + sum_sq_b[j-1]);
            }
        }
        sumRed.push_back(sum_r);
        sumGreen.push_back(sum_g);
        sumBlue.push_back(sum_b);
        sumsqRed.push_back(sum_sq_r);
        sumsqGreen.push_back(sum_sq_g);
        sumsqBlue.push_back(sum_sq_b);
    }
    cout << "59";
}


long stats::getSum(char channel, pair<int,int> ul, int w, int h){
    //cout <<"getSum";

    long sum = 0;

//     long a = 0;
//     long b = 0;
//     long c = 0;

//     switch(channel) {
//         case 'r':
//             if (ul.first != 0) {
//                 a = sumRed[ul.first - 1][ul.second + h-1];
//             }
//             if (ul.second != 0) {
//                 b = sumRed[ul.first + w-1][ul.second-1];
//             }
//             if (ul.first != 0 && ul.second != 0) {
//                 c = sumRed[ul.first -1][ul.second -1];
//             }

//             return  a + b - c;
//             break;

//         case 'g':
//             if (ul.first != 0) {
//                 a = sumGreen[ul.first - 1][ul.second + h-1];
//             }
//             if (ul.second != 0) {
//                 b = sumGreen[ul.first + w-1][ul.second-1];
//             }
//             if (ul.first != 0 && ul.second != 0) {
//                 c = sumGreen[ul.first -1][ul.second -1];
//             }

//             return  a + b - c;
//             break;

//         case 'b':
//             if (ul.first != 0) {
//                 a = sumBlue[ul.first - 1][ul.second + h-1];
//             }
//             if (ul.second != 0) {
//                 b = sumBlue[ul.first + w-1][ul.second-1];
//             }
//             if (ul.first != 0 && ul.second != 0) {
//                 c = sumBlue[ul.first -1][ul.second -1];
//             }

//             return  a + b - c;
//             break;
//     }
// }

    if (ul.first == 0 && ul.second == 0) {
        if (channel == 'r') {
            sum = sumRed[ul.first + w - 1][ul.second + h - 1];
        } else if(channel == 'g') {
            sum = sumGreen[ul.first + w - 1][ul.second + h - 1];
        } else if (channel == 'b') {     
            sum = sumBlue[ul.first + w - 1][ul.second + h - 1];
        }
    } else if (ul.first == 0) {
        if (channel == 'r') {
            sum = sumRed[ul.first + w - 1][ul.second + h - 1] - sumRed[ul.first + w - 1][ul.second - 1];
        } else if(channel == 'g') {
            sum = sumGreen[ul.first + w - 1][ul.second + h - 1] - sumGreen[ul.first + w - 1][ul.second - 1];
        } else if (channel == 'b') {     
            sum = sumBlue[ul.first + w - 1][ul.second + h - 1] - sumBlue[ul.first + w - 1][ul.second - 1];
        }
    } else if (ul.second == 0) {
        if (channel == 'r') {
            sum = sumRed[ul.first + w - 1][ul.second + h - 1] - sumRed[ul.first - 1][ul.second + h - 1];
        } else if(channel == 'g') {
            sum = sumGreen[ul.first + w - 1][ul.second + h - 1] - sumGreen[ul.first - 1][ul.second + h - 1];
        } else if (channel == 'b') {     
            sum = sumBlue[ul.first + w - 1][ul.second + h - 1] - sumBlue[ul.first - 1][ul.second + h - 1];
        }
    } else {
        if (channel == 'r') {
            sum = sumRed[ul.first + w - 1][ul.second + h - 1] + sumRed[ul.first - 1][ul.second - 1];
            sum = sum - sumRed[ul.first - 1][ul.second + h - 1] - sumRed[ul.first + w - 1][ul.second - 1];
        } else if(channel == 'g') {
            sum = sumGreen[ul.first + w - 1][ul.second + h - 1] + sumGreen[ul.first - 1][ul.second - 1];
            sum = sum - sumGreen[ul.first - 1][ul.second + h - 1] - sumGreen[ul.first + w - 1][ul.second - 1];
        } else if (channel == 'b') {     
            sum = sumBlue[ul.first + w - 1][ul.second + h - 1] + sumBlue[ul.first - 1][ul.second - 1];
            sum = sum - sumBlue[ul.first - 1][ul.second + h - 1] - sumBlue[ul.first + w - 1][ul.second - 1];
        }
    }
    //cout <<"getSum";
    return sum;
}

long stats::getSumSq(char channel, pair<int,int> ul, int w, int h){
    //cout <<"getSumSq";

//     long a = 0;
//     long b = 0;
//     long c = 0;

//     switch(channel) {
//         case 'r':
//             if (ul.first != 0) {
//                 a = sumsqRed[ul.first - 1][ul.second + h-1];
//             }
//             if (ul.second != 0) {
//                 b = sumsqRed[ul.first + w-1][ul.second-1];
//             }
//             if (ul.first != 0 && ul.second != 0) {
//                 c = sumsqRed[ul.first -1][ul.second -1];
//             }

//             return  a + b - c;
//             break;

//         case 'g':
//             if (ul.first != 0) {
//                 a = sumsqGreen[ul.first - 1][ul.second + h-1];
//             }
//             if (ul.second != 0) {
//                 b = sumsqGreen[ul.first + w-1][ul.second-1];
//             }
//             if (ul.first != 0 && ul.second != 0) {
//                 c = sumsqGreen[ul.first -1][ul.second -1];
//             }

//             return  a + b - c;
//             break;

//         case 'b':
//             if (ul.first != 0) {
//                 a = sumsqBlue[ul.first - 1][ul.second + h-1];
//             }
//             if (ul.second != 0) {
//                 b = sumsqBlue[ul.first + w-1][ul.second-1];
//             }
//             if (ul.first != 0 && ul.second != 0) {
//                 c = sumsqBlue[ul.first -1][ul.second -1];
//             }

//             return  a + b - c;
//             break;
//     }
// }
    long sum = 0;

    if (ul.first == 0 && ul.second == 0) {
        if (channel == 'r') {
            sum = sumsqRed[ul.first + w - 1][ul.second + h - 1];
        } else if(channel == 'g') {
            sum = sumsqGreen[ul.first + w - 1][ul.second + h - 1];
        } else if (channel == 'b') {     
            sum = sumsqBlue[ul.first + w - 1][ul.second + h - 1];
        }
    } else if (ul.first == 0) {
        if (channel == 'r') {
            sum = sumsqRed[ul.first + w - 1][ul.second + h - 1] - sumsqRed[ul.first + w - 1][ul.second - 1];
        } else if(channel == 'g') {
            sum = sumsqGreen[ul.first + w - 1][ul.second + h - 1] - sumsqGreen[ul.first + w - 1][ul.second - 1];
        } else if (channel == 'b') {     
            sum = sumsqBlue[ul.first + w - 1][ul.second + h - 1] - sumsqBlue[ul.first + w - 1][ul.second - 1];
        }
    } else if (ul.second == 0) {
        if (channel == 'r') {
            sum = sumsqRed[ul.first + w - 1][ul.second + h - 1] - sumsqRed[ul.first - 1][ul.second + h - 1];
        } else if(channel == 'g') {
            sum = sumsqGreen[ul.first + w - 1][ul.second + h - 1] - sumsqGreen[ul.first - 1][ul.second + h - 1];
        } else if (channel == 'b') {     
            sum = sumsqBlue[ul.first + w - 1][ul.second + h - 1] - sumsqBlue[ul.first - 1][ul.second + h - 1];
        }
    } else {
        if (channel == 'r') {
            sum = sumsqRed[ul.first + w - 1][ul.second + h - 1] + sumsqRed[ul.first - 1][ul.second - 1];
            sum = sum - sumsqRed[ul.first - 1][ul.second + h - 1] - sumsqRed[ul.first + w - 1][ul.second - 1];
        } else if(channel == 'g') {
            sum = sumsqGreen[ul.first + w - 1][ul.second + h - 1] + sumsqGreen[ul.first - 1][ul.second - 1];
            sum = sum - sumsqGreen[ul.first - 1][ul.second + h - 1] - sumsqGreen[ul.first + w - 1][ul.second - 1];
        } else if (channel == 'b') {     
            sum = sumsqBlue[ul.first + w - 1][ul.second + h - 1] + sumsqBlue[ul.first - 1][ul.second - 1];
            sum = sum - sumsqBlue[ul.first - 1][ul.second + h - 1] - sumsqBlue[ul.first + w - 1][ul.second - 1];
        }
    }
    return sum;
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int w, int h){
    //cout <<"getVar";
    if (w == 0 || h == 0) {
        return 0.0;
    }
    double r = getSumSq('r', ul, w, h) - getSum('r', ul, w, h) * getSum('r', ul, w, h)/(double)(w*h);
    double g = getSumSq('g', ul, w, h) - getSum('g', ul, w, h) * getSum('g', ul, w, h)/(double)(w*h);
    double b = getSumSq('b', ul, w, h) - getSum('b', ul, w, h) * getSum('b', ul, w, h)/(double)(w*h);
    return r + g + b;

}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int w, int h){
    //cout <<"getAvg";

    int r = getSum('r', ul, w, h) / (double)(w*h);
    int g = getSum('g',ul, w, h) / (double)(w*h);
    int b = getSum('b', ul, w, h) / (double)(w*h);
    RGBAPixel avg = RGBAPixel(r, g, b);
    return avg;
    
}