﻿#include<hgl/Graphics.h>                //GraphicsApplication,SystemInitInfo
#include<hgl/graph/Render.h>            //SetClearColor,ClearColorDepthBuffer
#include<hgl/graph/Shader.h>            //Shader
#include<hgl/object/FlowObject.h>       //FlowObject

using namespace hgl;
using namespace hgl::graph;

const uint16	vertex[]={	100,100,	//left,top
							356,356};	//width,height

class TestObject:public FlowObject
{
    VertexArray *vertex_data;		///<矩形顶点数据
    Renderable *rect_obj;			///<矩形可渲染对象

public:

    TestObject()
    {
        SetClearColor(ceMoziilaNightBlue);		//背景色使用暗夜蓝

        //创建矩形顶点数据
        {
            vertex_data=new VertexArray(HGL_PRIM_RECTANGLE);            ///<创建新的顶点数据对象，图元类型为矩形

            vertex_data->SetVertex(new VB4u16(1,vertex));               ///<设定矩形的坐标数据
        }

        {
            rect_obj=new Renderable(vertex_data);						///<创建可渲染对象

#ifdef _DEBUG
            rect_obj->AutoCreateShader(true,nullptr,OS_TEXT("rectangle"));	///<自动创建shader，DEBUG模式下如果是新生成shader，输出成指定文件名的文件
#else
            rect_obj->AutoCreateShader();									///<自动创建shader,正常模式下无参数
#endif//_DEBUG
        }
    }

    ~TestObject()
    {
        delete rect_obj;
        delete vertex_data;
    }

    void Draw(const Matrix4f *)
    {
        ClearColorDepthBuffer();

        DirectRender2D(rect_obj);
    }
};//class TestObject

HGL_GRAPHICS_APPLICATION("矩形图元","Rectangle",new TestObject());
