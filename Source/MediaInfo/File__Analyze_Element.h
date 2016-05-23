/*  Copyright (c) MediaArea.net SARL. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license that can
 *  be found in the License.html file in the root of the source tree.
 */

//---------------------------------------------------------------------------
#ifndef MediaInfo_File__Analyze_ELEMENTH
#define MediaInfo_File__Analyze_ELEMENTH
//---------------------------------------------------------------------------

#include "MediaInfo/MediaInfo_Config.h"
#include <string>
#include <sstream>
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//---------------------------------------------------------------------------
struct element_details
{
#if MEDIAINFO_TRACE
    class Element_Node_Data
    {
    public:

        enum Value_Output_Format
        {
            Format_Tree,
            Format_Xml,
        };

        enum Value_Type
        {
            ELEMENT_NODE_STR,
            ELEMENT_NODE_BOOL,
            ELEMENT_NODE_INT8U,
            ELEMENT_NODE_INT8S,
            ELEMENT_NODE_INT16U,
            ELEMENT_NODE_INT16S,
            ELEMENT_NODE_INT32U,
            ELEMENT_NODE_INT32S,
            ELEMENT_NODE_INT64U,
            ELEMENT_NODE_INT64S,
            ELEMENT_NODE_INT128U,
            ELEMENT_NODE_FLOAT32,
            ELEMENT_NODE_FLOAT64,
            ELEMENT_NODE_FLOAT80,
        };

        union Value
        {
            char*        Str;
            bool         b;
            int8u        i8u;
            int8s        i8s;
            int16u       i16u;
            int16s       i16s;
            int32u       i32u;
            int32s       i32s;
            int64u       i64u;
            int64s       i64s;
            float32      f32;
            float64      f64;
            float80      f80;
        };

        Element_Node_Data() : format_out(Format_Tree), is_empty(true) {}
        ~Element_Node_Data() { clear(); }

        Element_Node_Data& operator=(const Element_Node_Data&);
        void operator=(const std::string& v);
        void operator=(const Ztring& v);
        void operator=(bool v);
        void operator=(int8u v);
        void operator=(int8s v);
        void operator=(int16u v);
        void operator=(int16s v);
        void operator=(int32u v);
        void operator=(int32s v);
        void operator=(int64u v);
        void operator=(int64s v);
        void operator=(int128u v);
        void operator=(float32 v);
        void operator=(float64 v);
        void operator=(float80 v);

        void clear();
        bool empty();
        void set_AfterComma(int8u c) {AfterComma = c;}
        void Set_Output_Format(Value_Output_Format v) {format_out = v;}
        friend std::ostream& operator<<(std::ostream& os, const element_details::Element_Node_Data& v);

    private:
        //special case, uint128u has constructor, cannot be put in union
        int128u i128u;
        Value               val;
        Value_Type          type;
        Value_Output_Format format_out;
        bool                is_empty;
        // Use by float type
        int8u               AfterComma;

        Element_Node_Data(const Element_Node_Data&);
    };

    class Element_Node
    {
    public:
        Element_Node();
        Element_Node(const Element_Node& node);
        ~Element_Node();

        int64u                     Pos;             // Position of the element in the file
        int64u                     Size;            // Size of the element (including header and sub-elements)
        int64u                     Header_Size;     // Size of the header of the element
        std::string                Name;            // Name planned for this element
        Element_Node_Data          Value;           // The value (currently used only with Trace XML)
        std::vector<std::string>   Infos;           // More info about the element
        std::vector<Element_Node*> Children;        // Elements depending on this element
        std::string                Parser;          // Name of the parser for this element
        int32s                     Current_Child;   // Current child selected, used for param
        bool                       NoShow;          // Don't show this element
        bool                       OwnChildren;     // Child is owned by this node
        bool                       IsCat;

        void                       Init();          //Initialize with common values
        void Add_Child(Element_Node* node);         //Add a subchild to the current node

        // Print
        int Print(MediaInfo_Config::trace_Format Format, std::string& str);  //Print the node into str

    private:
        int Print_Xml(std::string& Str, size_t level);                       //Print the node in XML into str
        int Print_Tree(std::string& str, size_t level=1);                    //Print the node into str
        int Print_Tree_Cat(std::string& str, size_t level=1);
    };
#endif //MEDIAINFO_TRACE

    int64u       Code;               //Code filled in the file
    int64u       Next;               //
    bool         WaitForMoreData;    //This element is not complete, we need more data
    bool         UnTrusted;          //This element has a problem
    bool         IsComplete;         //This element is fully buffered, no need of more

#if MEDIAINFO_TRACE
    Element_Node TraceNode;
#endif //MEDIAINFO_TRACE
};

} //NameSpace

#endif // !MediaInfo_File__Analyze_ELEMENTH
