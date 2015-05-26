#include <node.h>
#include <v8.h>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace v8;

static const std::string base64_chars =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "abcdefghijklmnopqrstuvwxyz"
  "0123456789+/";


static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

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