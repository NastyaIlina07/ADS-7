// Copyright 2021 NNTU-CS
#include "train.h"
#include <iostream>
Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
  if (!first) return;

  Car* current = first->next;
  while (current != first) {
    Car* nextCar = current->next;
    delete current;
    current = nextCar;
  }
  delete first;
  first = nullptr;
}

void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};
  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
}

int Train::getLength() {
  if (!first) return 0;
  countOp = 0;
  Car* curr = first;
  if (!curr->light) {
    curr->light = true;
    countOp++;
  }
  int steps = 0;
  while (true) {
    curr = curr->next;
    steps++;
    countOp++;
    if (curr->light) {
      curr->light = false;
      countOp++;
      for (int i = 0; i < steps; i++) {
        curr = curr->prev;
        countOp++;
      }
      if (curr == first && !curr->light) {
        return steps;
      }

      steps = 0;
    }
  }
}

int Train::getOpCount() { return countOp; }
