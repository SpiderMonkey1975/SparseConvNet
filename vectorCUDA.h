#pragma once
#include <vector>
#include "cudaUtilities.h"
//General vector-y object, transferable between CPU and GPU memory
//Todo: Replace with CUDA 6.0+ Unified memory??
//Todo: Async memory copies during batch preparation

template <typename t> class vectorCUDA {
private:
  t* d_vec;
  int dsize; //Current size when on the GPU
  int dAllocated; //Allocated space on the GPU (>=dsize)
  std::vector<t> vec;
public:
  vectorCUDA(bool onGPU=true, int dsize=0);
  ~vectorCUDA();
  bool onGPU;
  void copyToCPU();
  void copyToGPU();
  void copyToCPUAsync(cudaMemStream &memStream);
  void copyToGPUAsync(cudaMemStream &memStream);
  t*& dPtr();
  std::vector<t>& hVector();
  int size();
  float meanAbs(float negWeight=1);
  void multiplicativeRescale(float multiplier);
  void setZero();
  void setZero(cudaMemStream &memStream);
  void setConstant(float a=0);
  void setUniform(float a=0,float b=1);
  void setBernoulli(float p=0.5);
  void setNormal(float mean=0, float sd=1);
  void resize(int n);
  void printSubset(const char *name, int nCol,int maxPrint=10);
  void check(const char* file = 0, int linenumber = 0);
};
