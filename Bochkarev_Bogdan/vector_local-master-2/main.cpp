//
//  main.cpp
//  Vector_1.0
//
//  Created by Bogdan Bochkarev on 11/11/20.
//  Copyright © 2020 Bogdan Bochkarev. All rights reserved.
//

#include "logic.hpp"

int main(int argc, const char * argv[]) {
    Vector<double> v1(5) ;
    Vector<double> v2 = {5.0};
    Vector<double> v3 = v2;
    Vector<char> vs(6);
    vs[0] = 'a';
    vs.set(5, 'N');
    Vector<std::string> vc(6);
    vc[3] = "abc";
    std::cout << v3.get(0) << std::endl;
    v3.set(0, 4.0);
    Vector<std::string> vc1 = vc;
    
    vc.push_back("sad");
    
    Vector<double> vi = {1., 2., 3., 4.};
    for (int i=0; i<v1.size(); ++i) {
        v1[i] = 1.1*i;
        std::cout << "v[" << i << "]==" << v1.get(i) << std::endl;
    }
    for (int i=0; i<v2.size(); ++i) {
        std::cout << "v[" << i << "]==" << v2.get(i) << std::endl;
    }
    for (int i=0; i<v3.size(); ++i) {
        std::cout << "v[" << i << "]==" << v3.get(i) << std::endl;
    }
    for (int i=0; i<vs.size(); ++i) {
        std::cout << "v[" << i << "]==" << vs[i] << std::endl;
    }
    for (int i=0; i<vc.size(); ++i) {
        std::cout << "v[" << i << "]==" << vc[i] << std::endl;
    }
    for (int i=0; i<vc1.size(); ++i) {
        std::cout << "v[" << i << "]==" << vc1[i] << std::endl;
    }
    for (int i=0; i<vi.size(); ++i) {
        std::cout << "v[" << i << "]==" << vi[i] << std::endl;
    }
    return 0;
}
