#ifndef BVH_ONLY_HEADER_PARSER
#define BVH_ONLY_HEADER_PARSER

//stl includes
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <inttypes.h>
#include <iostream>


//classic typedefs
using bvh_i64 = int64_t;
using bvh_u64 = uint64_t;
using bvh_i32 = int32_t;
using bvh_u32 = uint32_t;
using bvh_i16 = int16_t;
using bvh_u16 = uint16_t;
using bvh_i8 = int8_t;
using bvh_u8 = uint8_t;
using bvh_decimal = float;


namespace bvh
{
    //typedefs in namespace
    template<typename _Ptr>
    using Weak = std::weak_ptr<_Ptr>;

    template<typename _Ptr>
    using Shared = std::shared_ptr<_Ptr>;
    
}

namespace bvh
{
    struct _joint;
    using bvhJoint = _joint;
    
    class System
    {
    private:
        System();

    private:
        bvh_u64 left_curley_counter;
        bvh_u64 right_curley_counter;
        bvh_u64 layer;
        bvh_u64 motion_start;
        bvh_decimal frames;
        bvh_decimal frame_time;
        bvh_u64 channel_count;
        std::vector<bvh_u64> channel_element_count;
        std::ifstream file;

    private:
        using Token = enum class _token
        {
            LCURLEY = '{',
            RCURLEY = '}'
        };

        using Key = enum class _key
        {
            HIERARCHY = 0,
            ROOT,
            OFFSET,
            CHANNELS,
            JOINT,
            End_Site,
            MOTION,
            Frames,
            Frame_Time
        };

        static inline std::array<std::string, 9> Keywords {
        "HIERARCHY", 
        "ROOT", 
        "OFFSET",
        "CHANNELS",
        "JOINT",
        "End Site",
        "MOTION",
        "Frames",
        "Frame Time"
        };


    friend bvhJoint* bvhParse(const char* file_path) noexcept;
    };

#if 0
    using bvhJoint = struct _joint
    {
        Weak<_joint> parent;
        std::vector<bvh_decimal> offset;
        std::vector<Shared<_joint>> joints;
    };
#else
    using bvhJoint = struct _joint
    {
        _joint(const bvh_u64& _layer, const std::vector<bvh_decimal>& off, const std::vector<std::vector<bvh_decimal>>& chn):
        layer(_layer), offset(off), channels(chn)
        {

        }
        ~_joint()
        {
            for(auto& j : joints)
            {
                if(j)
                {
                    delete j;
                    //std::cout << "del:" << j->layer << " , \n";
                }
            }
            //std::cout << "del_main:" << layer << " \n";
        }

        _joint* parent = nullptr;
        std::vector<bvh_decimal> offset;
        std::vector<std::vector<bvh_decimal>> channels;
        std::vector<_joint*> joints;
        bvh_u64 layer;
    };
#endif

    bvhJoint* bvhParse(const char* file_path) noexcept;

}

bvh::System::System()
{
    left_curley_counter = 0;
    right_curley_counter = 0;
}

void putTab(bvh_u64 num)
{
    for(bvh_u64 i = 0; i < num; i++)
    {
        std::cout << "\t";
    }
}

bvh::bvhJoint* bvh::bvhParse(const char* file_path) noexcept
{
    bvh::System sys;
    sys.file.open(file_path);
    char letter;
    std::string word;
    
    //Shared<bvhJoint> root;
    bvh::bvhJoint* root = new bvh::bvhJoint(0, {0, 0, 0}, {{0}});
    bvh::bvhJoint*& ref = root;

    std::vector<std::string> w_count;
    std::vector<bvh_u64> l_count;

    if(sys.file.is_open())
    {
        while (sys.file >> word)
        {
            w_count.push_back(word);
            for(bvh_u64 i = 0; i < word.size(); i++)
            {
                letter = word[i];
                
                sys.layer = sys.left_curley_counter - sys.right_curley_counter;

                switch (letter)
                {
                case static_cast<bvh_i8>(System::Token::LCURLEY) :
                {
                    sys.left_curley_counter++;
                    break;
                }
                
                case static_cast<bvh_i8>(System::Token::RCURLEY) :
                {
                    sys.right_curley_counter++;
                    break;
                }

                default:
                    break;
                }
            }

            if(word == System::Keywords[static_cast<bvh_u64>(System::Key::CHANNELS)])
            {
                sys.channel_count++;
            }

            if(word != System::Keywords[static_cast<bvh_u64>(System::Key::MOTION)])
            {
                l_count.push_back(sys.layer);
            }
            else
                sys.motion_start = w_count.size();
            
        }

        sys.file.close();

        for(bvh_u64 i = 0; i < l_count.size(); i++)
        {
            if(w_count[i] == System::Keywords[static_cast<bvh_u64>(System::Key::CHANNELS)])
            {
                sys.channel_element_count.push_back(std::stoul(w_count[i + 1]));
            }
        }
    }
    else
    {
        std::cout << "file couldn't open!" << "\n";
    }
    
    std::cout << "{ count :" << sys.left_curley_counter << "\n";
    std::cout << "} count :" << sys.right_curley_counter << "\n";

    //sys.motion_start Frames:
    sys.motion_start++; 
    sys.frames = std::stof(w_count[sys.motion_start]);
    sys.motion_start++; //Frame
    sys.motion_start++; //Time:
    sys.motion_start++;
    sys.frame_time = std::stof(w_count[sys.motion_start]);
    sys.motion_start++; //
    //channels
//değiş
    sys.channel_count = 31;
//
    bvh_u64 all_channel_data_count = (sys.channel_count * 3) + 3;
    int num = 6;
    std::vector<std::vector<std::vector<bvh_decimal>>> chnsss;
    for(bvh_u64 u = 0; u < all_channel_data_count; u += num)
    {
        std::vector<std::vector<bvh_decimal>> chn;
        for(bvh_i64 z = 0; z < sys.frames; z++)
        {
            std::vector<bvh_decimal> frm;
            for(bvh_i64 k = u; k < u + num; k++)
            {
#ifdef BVH_SHOW_DEBUG
                std::cout << (z * all_channel_data_count) + k << " "; //
                std::cout << w_count[sys.motion_start + (z * all_channel_data_count) + k] << std::endl;
#endif
                frm.push_back(std::stof(w_count[sys.motion_start + (z * all_channel_data_count) + k]));
            }
#ifdef BVH_SHOW_DEBUG
            std::cout << "\n";
#endif
            chn.push_back(frm);///problem
        }
        chnsss.push_back(chn);
        num = 3;
    }


    bvh_i64 index_for_chnnsss = 0;
    for(bvh_u64 i = 0; i < l_count.size(); i++)
    {
        std::string str_index = w_count[i];
        bvh_u64 index = l_count[i];

        if(str_index == "{")
        {
            //offset
            std::vector<bvh_decimal> off;
            for(bvh_i64 t = i + 2; t < i + 5; t++)
            {
                off.push_back(std::stof(w_count[t]));
            }

            //Endside ları da joint sayınca chnss[i]' nin size'ı yetmiyor galiba...belki
            root->joints.push_back(new bvhJoint(index, off, chnsss[index_for_chnnsss]));//chnsss[i]
            root->joints[root->joints.size() - 1]->parent = root;
            root = root->joints[root->joints.size() - 1];
#ifdef BVH_SHOW_DEBUG
            for(bvh_i64 t = 0; t < 3; t++)
            {
                std::cout << root->offset[t] << " ";
            }
#endif //BVH_SHOW_DEBUG
            std::cout << std::endl;
            index_for_chnnsss++;
        }

        if(str_index == "}")
        {
            root = root->parent;
#ifdef BVH_SHOW_DEBUG
            std::cout << index_for_chnnsss-- << " ";
#endif //BVH_SHOW_DEBUG
            index_for_chnnsss--;
        }

    }

#ifdef BVH_SHOW_DEBUG
    std::cout << root->joints.size() << "\n";
#endif //BVH_SHOW_DEBUG
    

////////////////////////////////////////////////////////////////////////
    

    return root;
}




#endif //BVH_ONLY_HEADER_PARSER