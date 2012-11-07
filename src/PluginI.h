// -*- mode: c++; coding: utf-8 -*-

#ifndef PLUGIN_H
#define PLUGIN_H

#include <Ice/Ice.h>

class PluginI : public Ice::Plugin {
public:

  void initialize();
  void destroy();

};

#endif // PLUGIN_H
