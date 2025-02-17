

#include "VP.h"

#include "../nodes/vp_image_src_node.h"
#include "../nodes/infers/vp_trt_vehicle_plate_detector_v2.h"
#include "../nodes/osd/vp_plate_osd_node.h"
#include "../nodes/vp_screen_des_node.h"
#include "../utils/analysis_board/vp_analysis_board.h"

/*
* ## plate recognize sample ##
* detect and recognize plate in the whole frame
*/

#if plate_recognize_sample

int main() {
    VP_SET_LOG_LEVEL(vp_utils::vp_log_level::INFO);
    VP_LOGGER_INIT();

    // create nodes
    auto image_src_0 = std::make_shared<vp_nodes::vp_image_src_node>("image_src_0", 0, "./images/plates_/plate%d.jpg", 1);
    auto plate_detector = std::make_shared<vp_nodes::vp_trt_vehicle_plate_detector_v2>("plate_detector", "./models/trt/plate/det_2.trt", "./models/trt/plate/rec.trt");
    auto osd_0 = std::make_shared<vp_nodes::vp_plate_osd_node>("osd_0", "../third_party/paddle_ocr/font/NotoSansCJKsc-Medium.otf");
    auto screen_des_0 = std::make_shared<vp_nodes::vp_screen_des_node>("screen_des_0", 0);

    // construct pipeline 
    plate_detector->attach_to({image_src_0});
    osd_0->attach_to({plate_detector});
    screen_des_0->attach_to({osd_0});

    // start pipeline
    image_src_0->start();

    // visualize pipeline for debug
    vp_utils::vp_analysis_board board({image_src_0});
    board.display();
}

#endif