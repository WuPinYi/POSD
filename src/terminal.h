#ifndef TERMINAL_H
#define TERMINAL_H

#include "sort.h"
#include "shape.h"
#include "ellipse.h"
#include "triangle.h"
#include "circular_sector.h"
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <stdexcept>
#include <sstream>
using namespace std;

class Terminal
{
public:
    // you can use regular expression to get useful token from "Input string"
    Terminal(string inputString): _inputString(inputString)
    {
        if (_inputString == "") _incompleteInputstring = true;
        else
        {
            getContent();
            splitContent();
            getArgument();
            buildShapesInstance();
        }   
    }

    std::string showResult()
    {
        // ..... // return result For example: [XXX, XXX, XXX]
        if (_incompleteInputstring) 
        {
            throw std::string("Unuseful User Input!");
        }else
        {
            sortShape();
            for (int i = 0; i < _shapeList->size(); i++)
            {       
                if (_feature == "area"){
                    _result += to_string((*_shapeList)[i]->area());
                }
                else if (_feature == "perimeter"){
                    _result += to_string((*_shapeList)[i]->perimeter());
                }
                else if (_feature == "sumOfSquares"){
                    // cout <<"asdf" <<to_string((*_shapeList)[i]->sumOfSquares())<<endl;
                    _result += to_string((*_shapeList)[i]->sumOfSquares());
                }
                if (i != _shapeList->size() - 1)
                {
                    _result += ", ";
                }
            }
            _result += "]";
        }
        return _result;
    }
private:
    bool _incompleteInputstring = false;
    string _inputString;
    vector<string> _elements;
    string _feature;
    string _order;
    vector<string> _shapesElement;
    vector<string> _shapeParameters;
    vector<Shape*>* _shapeList = new vector<Shape*>();
    string _result = "[";
    // get content from input string
    void getContent()
    {
        regex validForm("[A-z]|[0-9]|[,]|[()]|[-]");
        // _inputString = "Ellipse ( 6,5) Triangle (3,0,0,2,-3,zero) CircularSector (8,40) area inc";
        string Wordiness = regex_replace(_inputString, validForm, "") ;
        regex r("["+Wordiness+"]");
        _inputString = regex_replace(_inputString, r, "");   
    }
    // split content by ) and push into vector
    void splitContent()
    {
        std::regex rgx("[)]");
        std::sregex_token_iterator iter(_inputString.begin(),_inputString.end(),rgx,-1);
        std::sregex_token_iterator end;
        for ( ; iter != end; ++iter){
            _elements.push_back(*iter);
        }
    }
    // get right argument from 
    void getArgument()
    {
        int eSize = _elements.size();
        string lastWord = _elements[eSize-1];
        bool find = false;
        // check if have feature and order or not
        for (int i= 0;i< lastWord.length();i++){
            if (lastWord[i]=='(') find = true;
        }
        // if no
        if(find){
            _incompleteInputstring = true;
        }else{// if have
            for(int j=0; j<eSize; j++){
                if(j!=_elements.size()-1){
                    _elements.at(j) = _elements[j]+")";
                }
            }
            _feature = _elements.back().substr(0, _elements.back().size()-3);
            _order = _elements.back().substr(_elements.back().size()-3, _elements.back().size());
            // cout <<"feature = " <<_feature << endl<< "_order = " << _order << endl;
            if ((_order == "inc" || _order == "dec") && (_feature == "area" || _feature == "perimeter" || _feature == "sumOfSquares")) 
            {
                _incompleteInputstring = false;
            }else 
            {
                _incompleteInputstring = true;
            }
            _elements.pop_back();
        }
    }
    // add space to shapes string
    void addSpace(){
        for(int i=0; i<_elements.size(); ++i)
        {
            string elems = _elements[i];
            int pos = elems.find("(", 0);
            if (pos > 0)
            {
                elems.insert(pos, " ");
                _elements.at(i) = elems; 
            }
        }
    }
    // build shape instance
    void buildShapesInstance()
    {
        addSpace();
        int elementSize = _elements.size();
        for (int i = 0; i <elementSize ; i++)
        {
            bool error = true;
            // split element and parameters
            _shapesElement = split(_elements[i], " ");
            _shapeParameters = split(_shapesElement[1], ",");
            // remove ()
            for(int j=0 ; j<_shapeParameters.size();j++){
                regex invalidForm("[^0-9+,+A-z+-]");
                _shapeParameters[j] = regex_replace(_shapeParameters[j], invalidForm, "") ;
            }
            // remove invalid parameter (zero)
            for (int j=0 ; j<_shapeParameters.size();j++)
            {
                regex e ("([-]?)+[0-9]+([.]?)+[0-9]?");
                if (!regex_match (_shapeParameters[j],e)) error = false;
            }
            // shape Instance
            if (error){
                if (_shapesElement[0] == "Ellipse" && _shapeParameters.size() == 2)
                {
                    _shapeList->push_back(new Ellipse(atof(_shapeParameters[0].c_str()), atof(_shapeParameters[1].c_str())));
                }
                else if (_shapesElement[0] == "CircularSector" && _shapeParameters.size() == 2) 
                {
                    _shapeList->push_back(new CircularSector(atof(_shapeParameters[0].c_str()), atof(_shapeParameters[1].c_str())));
                }
                else if (_shapesElement[0] == "Triangle" && _shapeParameters.size() == 6)
                {
                    _shapeList->push_back(new Triangle(atof(_shapeParameters[0].c_str()),atof(_shapeParameters[1].c_str()),atof(_shapeParameters[2].c_str()),atof(_shapeParameters[3].c_str()),atof(_shapeParameters[4].c_str()),atof(_shapeParameters[5].c_str())));
                }else 
                {
                    continue;
                }
            }
        }
    }
    // sort shapes
    void sortShape()
    {
        Sort* sortShape = new Sort(_shapeList);
        if (_order == "dec"){
            sortShape->quickSort(DescendingComparison(_feature));
        }
        else if (_order == "inc"){
            sortShape->quickSort(AscendingComparison(_feature));
        }
    }
    vector<string> split(const string& str, const string& delim) 
    {
        vector<string> res;
        // string to char
        char *strs = new char[str.length() + 1];
        // strcpy(copied, input)
        strcpy(strs, str.c_str()); 
        char *d = new char[delim.length() + 1];
        strcpy(d, delim.c_str());
        char *p = strtok(strs, d);
        while(p) 
        {
            string s = p;
            res.push_back(s);
            p = strtok(NULL, d);
        }
        return res;
    }

};
#endif