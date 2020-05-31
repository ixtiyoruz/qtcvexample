#include "utils.h"
//here comes global libraries

// executing commands
std::string exec(const char* cmd){
   std::array<char, 128> buffer;
   std::string result;
   std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
   if (!pipe) {
       throw std::runtime_error("popen() failed!");
   }
   while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
       result += buffer.data();
   }
   return result;
}

// finding cameras from linux using v4l2 ( v4l2 must be installed)
std::vector<camera_info> find_cameras_linux(){
    std::vector<camera_info> res;
    std::string camera_v4l2_result = exec("v4l2-ctl --list-devices");

    std::vector< std::string > SplitVec;
    split(SplitVec, camera_v4l2_result, boost::is_any_of("\n"),boost::token_compress_off);
    int num_of_cameras = SplitVec.size()/3;
    for(int i=0;i < num_of_cameras;i+=1){
        camera_info tmp;
        tmp.name = SplitVec[i*3];
        tmp.path = SplitVec[i*3 + 1];
        res.push_back(tmp);
    }
    return res;
}
