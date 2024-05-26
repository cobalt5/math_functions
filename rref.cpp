//WRONG

#include <iostream>
#include <math.h>
#include <vector>
#include <string>
class fraction{
    public:
        //store the sign in the numerator
        long long numerator;
        long long denominator;
};

fraction addFraction(fraction a, fraction b){
    //find the smallest common denominator if I want to optimize this further, for now just cross multiply
    fraction sum;
    sum.numerator = a.denominator*b.numerator+b.denominator*a.numerator;
    sum.denominator = a.denominator*b.denominator;
    return sum;
}
fraction subtractFraction(fraction a, fraction b){
    //b is the subtraction
    fraction diff;
    diff.numerator = b.denominator*a.numerator-b.numerator*a.denominator;
    diff.denominator = a.denominator*b.denominator;
    return diff;
}
fraction multiplyFraction(fraction a, fraction b){
    fraction product;
    product.numerator = a.numerator*b.numerator;
    product.denominator = a.denominator*b.denominator;
    return product;
}
fraction divideFraction(fraction a, fraction b){
    //b is the divisor
    fraction bNew;
    //bNew is going to be the inverse of b
    bNew.numerator = b.denominator;
    bNew.denominator = b.numerator;
    return multiplyFraction(a, bNew);
}
fraction reciprocol(fraction m){
    fraction n;
    n.numerator = m.denominator;
    n.denominator = m.numerator;
    return n;
}
void printFraction(fraction n){
    std::cout << n.numerator << '/' << n.denominator;
}
fraction fractionParser(std::string s){
    fraction parsedFraction;
    size_t slashIndex = s.find('/');
    if(slashIndex > s.size()-1){
        parsedFraction.numerator = std::stoi(s);
        parsedFraction.denominator = 1;
        return parsedFraction;
    }
    std::string numeratorStr = s.substr(0, slashIndex);
    std::string denominatorStr = s.substr(slashIndex + 1);
    parsedFraction.numerator = std::stoi(numeratorStr);
    parsedFraction.denominator = std::stoi(denominatorStr);
    return parsedFraction;
}
fraction simplifyFraction(fraction n){
    long long n1 = n.numerator;
    long long n2 = n.denominator;
    if(n1 == 0){
        n.denominator = 1;
        return n;
    }
    if(n1 == n2){
        n.numerator = 1;
        n.denominator = 1;
        return n;
    }
    bool isNeg = 0;
    if(n1 < 0 || n2<0){
        if(n1<0 && n2<0){
            n.numerator = abs(n.numerator);
            n.denominator = abs(n.denominator);
        }
        else if (n1<0){
            isNeg = 1;
        }
        else if (n2<0){
            isNeg = 1;
        }

    n1 = abs(n1);
    n2 = abs(n2);
    }
    // swapping variables n1 and n2 if n2 is greater than n1.
    if ( n2 > n1) {   
        long long temp = n2;
        n2 = n1;
        n1 = temp;
    }
    //n2 will always be the smaller one
    long long hcf;
    for (int i = 1; i <=  n2; ++i) {
        if (n1 % i == 0 && n2 % i ==0) {
            hcf = i;
        }
    }

    n.numerator/=hcf;
    n.denominator/=hcf;
    if(n.denominator<0 && n.numerator >= 0){
        n.numerator *= -1;
        n.denominator = abs(n.denominator);
        
    }
    return n;
}
double fractionToDouble(fraction n){
    return (double)n.numerator/(double)n.denominator;
}
void printMatrix(std::vector<std::vector<fraction> > m){
    for(int i = 0; i<m.size(); ++i){
        for(int j = 0; j<m[0].size(); ++j){
            printFraction(m[i][j]);
            std::cout << ' ';
        }
        std::cout << "\n";
    }
}

void rref(std::vector<std::vector<fraction> >& m) {
    printMatrix(m);
    //TAKES A LIST BY REFERENCE
    for(int i = 0; i<m.size(); ++i){
        fraction multiple = reciprocol(m[i][i]);
        // std::cout << "multiplying row " << i << " by ";
        // printFraction(multiple);  
        // std::cout << "\n"; 
        for(int j = 0; j<m[0].size(); ++j){
            m[i][j] = multiplyFraction(m[i][j], multiple);
            m[i][j] = simplifyFraction(m[i][j]);
            // printFraction(m[i][j]);
            // std::cout << ' ';
        }

        for(int k = 0; k<m.size(); ++k){
            if(k==i){}
            else {
                //the multiple is literally just m[k][i]
                fraction multiple = m[k][i];
                // std::cout << "subtracting row " << k << " by ";
                // printFraction(m[k][i]);
                // std::cout << "* index";
                // std::cout << "\n";
                for(int l = 0; l<m[0].size(); ++l){
                    
                    m[k][l] = subtractFraction(m[k][l],multiplyFraction(multiple,m[i][l]));
                    m[k][l] = simplifyFraction(m[k][l]);
                    // std::cout << "subtracting by ";
                    // printFraction(multiplyFraction(multiple,m[i][l]));
                    // std::cout << "we get: ";
                    // printFraction(m[k][l]); std::cout << "\n";
                }
            }

        }
        for(int i = 0; i<m.size(); ++i){
            for(int j = 0; j<m[0].size(); ++j){
                m[i][j] = simplifyFraction(m[i][j]);
            }
        }
        // if(i == 2){
        //     int counter = 0;
        //     while(1){
        //         if(counter == 1){
        //             break;
        //         }
        //         printMatrix(m);
        //         counter++;
                 
        //     }
        // }
    }
    for(int i = 0; i<m.size(); ++i){
        m[i][m[0].size()-1] = simplifyFraction(m[i][m[0].size()-1]);
    }
}

std::string pointFunction(std::vector<std::vector<fraction> > points){

    std::string function;
    rref(points);
    printMatrix(points);
    std::cout << "f(x) = ";
    for(int i = 0; i<points.size(); ++i){
        printFraction(points[i][points[0].size()-1]);
        if(i!=points.size()-1){
            std::cout << "x^" << points.size()-i-1;
            std::cout << " + ";
        }
    }
    return function;
}

fraction exponential(fraction a, int b){
    //returns a^b
    fraction result = a;
    if(b == 0){
        result.numerator = 1;
        result.denominator = 1;
        return result;
    }
    for(int i = 0; i<b-1; ++i){
        result = multiplyFraction(result, a);
        result = simplifyFraction(result);
    }
    return result;
}
int main() {
    std::vector<std::vector<fraction> > m;
    int rows; int columns;
    std::cout << "type in the number of rows and columns\n";
    
    std::cin >> rows >> columns;
    if(rows != columns-1){
        std::cout << "wrong numbers bro\n";
        return -1;
    }
    std::cout << "type in the matrix\n";
    for(int i = 0; i<rows; ++i){
        std::vector<fraction> g;
        m.push_back(g);
        for(int j = 0; j<columns; ++j){
            std::string s;
            std::cin >> s;
            m[i].push_back(fractionParser(s));
        }
    }

    rref(m);
    //print m later
    std::cout << "\n";
    for(int i = 0; i<m.size(); ++i){
        for(int j = 0; j<m[0].size(); ++j){
            m[i][j] = simplifyFraction(m[i][j]);
            printFraction(m[i][j]);
            std::cout << ' ';
        }
        std::cout << "\n";
    }
    for(int i = 0; i<m.size(); ++i){
        for(int j = 0; j<m[0].size(); ++j){
            m[i][j] = simplifyFraction(m[i][j]);
            double l = fractionToDouble(m[i][j]);
            std::cout << l;
            std::cout << ' ';
        }
        std::cout << "\n";
    }
    
}