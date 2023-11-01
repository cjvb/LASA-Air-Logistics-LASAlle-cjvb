
//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//

/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array.
 *
 */

#include "slist.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

using namespace std;

// This function converts decimal degrees to radians
double deg2rad(double deg) { return (deg * pi / 180); }
//  This function converts radians to decimal degrees
double rad2deg(double rad) { return (rad * 180 / pi); }

double disKAUS(double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  double lon1d = -97.66989899;
  double lat1d = 30.19449997;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = (lat2r - lat1r);
  v =(lon2r - lon1r);
  double a = pow(sin(u / 2), 2)+pow(sin(v / 2), 2) * cos(lat1r)*cos(lat2r);
  double c = 2*asin(sqrt(a));
  return earthRadiusKm * c;
}

class Airport {
public:
  char code[5];
  double longitude;
  double latitude;
};

class Node {
public:
  Airport data;
  Node *next;

  Node(Airport d){
    this->data=d;
    this->next=NULL;
  }
};

class linkedlist {
public:
  Node *head;

  linkedlist() {
    this->head=NULL;
  }

  void append(Airport *ap) {
    Node *n = new Node(*ap);
    if (head == NULL) {
      head = n;
      return;
    } else {
      Node *temp = head;
      while (temp->next!=NULL) {
        temp = temp->next;
      }
      temp->next = n;
    }
  
  }

};

void simpleSortTotal(linkedlist *l){
  if (l->head == nullptr) return;
  Node *c = l->head;
  while (c->next!=NULL) {
    Node *j = c->next;
    while(j!=NULL){
    if (disKAUS(c->data.latitude, c->data.longitude) >
        disKAUS(j->data.latitude, j->data.longitude)) {
      swap(c->data, j->data);
    }
    j = j->next;
  }
  c = c->next;
  }
}
/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */

int main() {
  ifstream infile;
  int i = 0;
  char cNum[20];
  Airport *airportArr[22343]; // Replace array with Linked List
  int air = -1;
  // Airport* a[13500];

  infile.open("airport-codes_US.csv", ifstream::in);
  if (!infile.is_open()) {
    cout << "file didnt open" << endl;
    return -1;
  }

  int c = 0;
  while (infile.good()) {
    char temp[999];
    airportArr[c] = new Airport();
    infile.getline(airportArr[c]->code, 256, ',');
    infile.getline(temp, 256, ',');
    infile.getline(temp, 256, ',');
    infile.getline(cNum, 256, ',');
    airportArr[c]->longitude = atof(cNum);
    infile.getline(cNum, 256, ',');
    airportArr[c]->latitude = atof(cNum);
    infile.getline(temp, 256, '\n');

   // cout << airportArr[c]->code << " long: " << airportArr[c]->longitude
   //<< " lat: " << airportArr[c]->latitude << endl;

    /*
    if (!(c % 1000))
    {
        cout << airportArr[c]->code << " long: " << airportArr[c]->longitude
    << " lat: " << airportArr[c]->latitude <<  endl; cout <<
    airportArr[c+1]->code << endl; //" long: " << airportArr[c+1]->longitude
    << " lat: " << airportArr[c+1]->latitude <<  endl;
    } */
    i++;
    c++;
    air++;
  }
  infile.close();

  
  /*for (int b = 0; b < air; b++) {
    cout << airportArr[b]->code << " long: " << airportArr[b]->longitude
         << " lat: " << airportArr[b]->latitude << endl;
    cout << "Distance between " << airportArr[b]->code << " and KAUS is "
         << disKAUS(airportArr[b]->longitude, airportArr[b]->latitude)
         << endl;*/

  linkedlist *Alle = new linkedlist();

  for(int i = 0;i<air;i++){
    Alle->append(airportArr[i]);
  }
  

  simpleSortTotal(Alle);
  Node *temp = Alle->head;
  for(int i = 0;i<air;i++){
    
    cout << temp->data.code << " dist to KAUS: "<< disKAUS(temp->data.latitude, temp->data.longitude) << endl;
    temp = temp->next;
  }
  

  // while (current != NULL){
  //  cout << current->data.code << " long: " << current->data.longitude << "
  //  lat: " << current->data.latitude << endl; current = current->next;
  // }
 
}

/*
        Provide sort routine on linked list
*/
/*
void simpleSortTotal()
{
}
*/
