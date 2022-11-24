//
// Created by leolaxie on 2022/8/24.
//

//Product.h
#ifndef PRODUCT_H_
#define PRODUCT_H_

#include <iostream>

using namespace std;


class AbstractProduct
{
public:
    virtual ~AbstractProduct();


    virtual void ProductOperation() = 0;


};


class ConcreteProduct1 : public AbstractProduct
{
public:
    ConcreteProduct1();


    virtual ~ConcreteProduct1();


    virtual void ProductOperation();


};


class ConcreteProduct2 : public AbstractProduct
{
public:
    ConcreteProduct2();


    virtual ~ConcreteProduct2();


    virtual void ProductOperation();


};

//Product.cpp
//#include "Product.h"


//class AbstractProduct
AbstractProduct::~AbstractProduct()
{
    cout << "AbstractProduct::~AbstractProduct ()" << endl;
}


void AbstractProduct::ProductOperation()
{


    cout << "void AbstractProduct::ProductOperation()" << endl;
}


//class ConcreteProduct1
ConcreteProduct1::ConcreteProduct1()
{
    cout << "ConcreteProduct1::ConcreteProduct1()" << endl;
}


ConcreteProduct1::~ConcreteProduct1()
{
    cout << "ConcreteProduct1::~ConcreteProduct1()" << endl;
}


void ConcreteProduct1::ProductOperation()
{
    cout << "void ConcreteProduct1::ProductOperation()" << endl;
}


//class ConcreteProduct2
ConcreteProduct2::ConcreteProduct2()
{
    cout << "ConcreteProduct2::ConcreteProduct2()" << endl;
}


ConcreteProduct2::~ConcreteProduct2()
{
    cout << "ConcreteProduct2::~ConcreteProduct2()" << endl;
}


void ConcreteProduct2::ProductOperation()
{
    cout << "void ConcreteProduct2::ProductOperation()" << endl;
}

//Factory.h
#ifndef FACTORY_H_
#define FACTORY_H_

using namespace std;

class AbstractProduct;

class AbstractFactory
{
public:
    virtual ~AbstractFactory();


    virtual AbstractProduct *CreateProduct() = 0;


};


AbstractFactory::~AbstractFactory()
{
    cout << "AbstractFactory::~AbstractFactory()" << endl;
}


template<class T>
class TStandardFactory : public AbstractFactory
{
public:
    TStandardFactory();

    virtual ~TStandardFactory();

    virtual AbstractProduct *CreateProduct();
};


template<class T>
TStandardFactory<T>::TStandardFactory()
{
    cout << "TStandardFactory<T>::TStandardFactory()" << endl;
}


template<class T>
TStandardFactory<T>::~TStandardFactory()
{
    cout << "TStandardFactory:: ~TStandardFactory()" << endl;
}


template<class T>
AbstractProduct *TStandardFactory<T>::CreateProduct()
{
    cout << "T* TStandFactory<T>::CreateProduct()" << endl;
    return new T();
}


#endif


#endif

//Client.h
//#include "Factory.h"
//#include "Product.h"
using namespace std;

int main()
{

    AbstractFactory *pFactory = new TStandardFactory<ConcreteProduct1>();
    AbstractProduct *pProduct = pFactory->CreateProduct();


    pProduct->ProductOperation();


    delete pProduct;
    delete pFactory;


    cout << endl << endl << endl;


    pFactory = new TStandardFactory<ConcreteProduct2>();
    pProduct = pFactory->CreateProduct();


    pProduct->ProductOperation();


    delete pProduct;
    delete pFactory;

}