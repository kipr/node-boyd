#include <node.h>
#include <v8.h>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);


// BAD!?!? Fix me ('delete cap;' fails if we allocate cap on the heap (Windows only problem?))
// maybe related to http://answers.opencv.org/question/11294/delete-videocapture/
static cv::VideoCapture cap;


void open(const v8::FunctionCallbackInfo<v8::Value>& info)
{
  v8::Handle<v8::Object> ret = v8::Object::New(info.GetIsolate());
  ret->Set(v8::String::NewFromUtf8(info.GetIsolate(), "success"),
                                   v8::Boolean::New(info.GetIsolate(), cap.open(0)));

  info.GetReturnValue().Set(ret);
}


void close(const v8::FunctionCallbackInfo<v8::Value>& info)
{
  cap.release();

  info.GetReturnValue().Set(true);
}


void getImage(const v8::FunctionCallbackInfo<v8::Value>& info)
{
  cv::Mat im;
  cap.read(im);

  cv::Mat res;
  cv::resize(im, res, cv::Size(320, 240));

  std::vector<int> param;
  param.push_back(cv::IMWRITE_JPEG_QUALITY);
  param.push_back(90);

  std::vector<unsigned char> buff(320 * 240);

  cv::imencode(".jpg", res, buff, param);

  info.GetReturnValue().Set(v8::String::NewFromUtf8(info.GetIsolate(),
                                          base64_encode(&buff[0], buff.size()).c_str()));
}

void init(v8::Handle<v8::Object> exports)
{
  NODE_SET_METHOD(exports, "open", open);
  NODE_SET_METHOD(exports, "close", close);
  NODE_SET_METHOD(exports, "getImage", getImage);
}

NODE_MODULE(node_boyd, init)
