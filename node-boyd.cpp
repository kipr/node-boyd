#include <node.h>
#include <v8.h>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace v8;
std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);


// BAD!?!? Fix me ('delete cap;' fails if we allocate cap on the heap (Windows only problem?))
// maybe related to http://answers.opencv.org/question/11294/delete-videocapture/
static cv::VideoCapture cap;

Handle<Value> open(const Arguments &args)
{
  HandleScope scope;
  
  Handle<Object> ret = Object::New();
  
  ret->Set(String::New("success"), Boolean::New(cap.open(0)));
  
  if(!cap.isOpened())
  {
    return scope.Close(ret);
  }
  
  Handle<Object> handle = Object::New();
  
  ret->Set(String::New("handle"), handle);
  
  return scope.Close(ret);
}

Handle<Value> close(const Arguments &args)
{
  HandleScope scope;
  
  cap.release();
  
  return scope.Close(Boolean::New(true));
}

Handle<Value> getImage(const Arguments &args)
{
  HandleScope scope;
  
  cv::Mat im;
  cap.read(im);
  
  cv::Mat res;
  cv::resize(im, res, cv::Size(320, 240));
  
  std::vector<int> param;
  param.push_back(cv::IMWRITE_JPEG_QUALITY);
  param.push_back(90);
  
  std::vector<unsigned char> buff(320 * 240);
  
  cv::imencode(".jpg", res, buff, param);
  
  return scope.Close(String::New(base64_encode(&buff[0], buff.size()).c_str()));
}

void init(Handle<Object> target)
{
  target->Set(String::NewSymbol("open"), FunctionTemplate::New(open)->GetFunction());
  target->Set(String::NewSymbol("close"), FunctionTemplate::New(close)->GetFunction());
  target->Set(String::NewSymbol("getImage"), FunctionTemplate::New(getImage)->GetFunction());
}

NODE_MODULE(node_boyd, init)