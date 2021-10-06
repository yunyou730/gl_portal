//
//  DFMacro.hpp
//  df
//
//  Created by bytedance on 2021/10/3.
//

#ifndef DFMacro_hpp
#define DFMacro_hpp


#define DF_SAFE_DEL(p) if(p){ delete p;p = nullptr;}

#define Interface class
#define implements :

#define NS_DF_BEGIN namespace df {
#define NS_DF_END }

#define NS_DF_ECS_BEGIN namespace df { namespace ecs {
#define NS_DF_ECS_END }}


#endif /* DFMacro_hpp */
