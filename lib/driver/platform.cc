/* Copyright 2015-2017 Philippe Tillet
* 
* Permission is hereby granted, free of charge, to any person obtaining 
* a copy of this software and associated documentation files 
* (the "Software"), to deal in the Software without restriction, 
* including without limitation the rights to use, copy, modify, merge, 
* publish, distribute, sublicense, and/or sell copies of the Software, 
* and to permit persons to whom the Software is furnished to do so, 
* subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be 
* included in all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <string>
#include "triton/driver/platform.h"
#ifdef __HIP_PLATFORM_AMD__
#include "triton/driver/device_hip.h"
#else
#include "triton/driver/device.h"
#endif


namespace triton
{
namespace driver
{


/* ------------------------ */
//         CUDA             //
/* ------------------------ */

std::string cu_platform::version() const{
  int version;
  dispatch::cuDriverGetVersion(&version);
  return std::to_string(version);
}

void cu_platform::devices(std::vector<device *> &devices) const{
  int N;
  dispatch::cuDeviceGetCount(&N);
  for(int i = 0 ; i < N ; ++i){
    CUdevice dvc;
    dispatch::cuDeviceGet(&dvc, i);
    devices.push_back(new driver::cu_device(dvc));
  }
}

/* ------------------------ */
//        Host              //
/* ------------------------ */

std::string host_platform::version() const {
  return "1.0";
}

void host_platform::devices(std::vector<driver::device*> &devices) const {
  devices.push_back(new driver::host_device());
}


}
}
