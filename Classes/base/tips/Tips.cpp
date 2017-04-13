#include "Tips.h"
#include "cocostudio/CocoStudio.h"
#include "../misc/MyActions.h"
#include "../misc/GlobalNode.h"
#include "../misc/MyMisc.h"

Tips* Tips::show() {
    Tips* tips = Tips::create();
    Director::getInstance()->getRunningScene()->addChild(tips);
    return tips;
}




bool Tips::init() {
    if (!Layer::init()) {
        return false;
    }

    rootNode = CSLoader::createNode("Tips.csb");
    this->addChild(rootNode);

    tipsNode = rootNode->getChildByName("tipsNode");
    tipsNode->runAction(MyActions::getInstance()->TipsOpen());

    captureNode = rootNode->getChildByName("captureNode");

    tipsNode->setVisible(false);
    std::string __blurImgName = "__forBlur.png";
    utils::captureScreen(CC_CALLBACK_2(Tips::afterCapture, this), __blurImgName);

    INITBTN(closeBtn, tipsNode, "closeBtn", [&](Ref*) {
        closeBtn->setEnabled(false);
        tipsNode->runAction(MyActions::getInstance()->TipsClose([&]() {
            //sprRemoveGray(forBlur);
            this->removeFromParent();
        }));
    });

    return true;
}

void Tips::afterCapture(bool succeed, const std::string& outputFile) {
    tipsNode->setVisible(true);
    if (succeed) {
        CCLOG("%s", outputFile.c_str());
        //ÏÔÊ¾½ØÍ¼
        forBlur = Sprite::create(outputFile);
        Size winSize = Director::getInstance()->getWinSize();
        forBlur->setPosition(winSize / 2);
        sprAddGray(forBlur);
        captureNode->addChild(forBlur);
    } else {
        CCLOG("Capture screen failed.");
    }
}

void Tips::sprAddGray(Sprite* sprite) {
    if (sprite) {
        GLProgram * p = new GLProgram();
        p->initWithFilenames("blur.vsh", "blur.fsh");
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        p->link();
        p->updateUniforms();
        sprite->setGLProgram(p);
        auto _programstate = GLProgramState::getOrCreateWithGLProgram(p);
        _programstate->setUniformVec2("resolution", Vec2(1136.0f, 640.0f));
        _programstate->setUniformVec2("direction", Vec2(1, 1));
        sprite->setGLProgramState(_programstate);
    }
}


void Tips::sprRemoveGray(Sprite * sprite) {
    if (sprite) {
        GLProgram * pProgram = CCShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP);
        sprite->setGLProgram(pProgram);
        CHECK_GL_ERROR_DEBUG();
    }
}