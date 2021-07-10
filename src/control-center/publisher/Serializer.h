// #ifndef SERIALIZER_H
// #define SERIALIZER_H

// #include "DriverWish.h"
// #include "PBDriverWish.pb.cc"
// #include "PBDriverWish.pb.h"
// #include <iostream>

// class Serializer {

// public:
//     virtual ~Serializer() = default;
//     std::string Serialize_Driver_Wish(DriverWish* driver_wish)
//     {
//         PBDriverWish::PBDriverWish pb_driver_wish;
//         std::string serialized_data;

//         pb_driver_wish.set_left_servo(driver_wish->left_servo);
//         pb_driver_wish.set_right_servo(driver_wish->right_servo);
//         pb_driver_wish.set_top_servo(driver_wish->top_servo);

//         pb_driver_wish.SerializeToString(&serialized_data);

//         return serialized_data;
//     }


// };

// #endif /* SERIALIZER_H */
