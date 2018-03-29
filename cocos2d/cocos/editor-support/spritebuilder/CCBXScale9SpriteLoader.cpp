#include "CCBXScale9SpriteLoader.h"
#include "ui/UIScale9Sprite.h"

NS_CC_BEGIN
namespace spritebuilder {
    
static const std::string PROPERTY_SPRITEFRAME("spriteFrame");
static const std::string PROPERTY_BLENDFUNC("blendFunc");
    
static const std::string PROPERTY_MARGIN("margin");
static const std::string PROPERTY_MARGIN_LEFT("marginLeft");
static const std::string PROPERTY_MARGIN_TOP("marginTop");
static const std::string PROPERTY_MARGIN_RIGHT("marginRight");
static const std::string PROPERTY_MARGIN_BOTTOM("marginBottom");
static const std::string PROPERTY_FLIP("flip");
static const std::string PROPERTY_RENDERINGTYPE("renderingType");

Scale9SpriteLoader *Scale9SpriteLoader::create()
{
    Scale9SpriteLoader *ret = new Scale9SpriteLoader();
    ret->autorelease();
    return ret;
}

Node *Scale9SpriteLoader::createNodeInstance(const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, CCBXReaderOwner *rootOwner, const ValueMap &customProperties, const NodeParams& params) const
{
    const SpriteFrameDescription &spriteFrame = getNodeParamValue(params, PROPERTY_SPRITEFRAME, _spriteFrame);
    ui::Scale9Sprite *sprite = _spriteFrame.spriteFrame?ui::Scale9Sprite::createWithSpriteFrame(spriteFrame.spriteFrame.get()):ui::Scale9Sprite::create();
    sprite->setAnchorPoint(Vec2(0.0f, 0.0f));
    return sprite;
}

void Scale9SpriteLoader::setSpecialProperties(Node* node, const Size &parentSize, float mainScale, float additionalScale, CCBXReaderOwner *owner, Node *rootNode, const cocos2d::ValueMap &customProperties, const NodeParams& params) const
{
    ui::Scale9Sprite *sprite = static_cast<ui::Scale9Sprite*>(node);
    const Vec4 &margins = getNodeParamValue(params, PROPERTY_MARGIN, _margins);
    Size size = sprite->getOriginalSize();
    sprite->setRenderingType((margins == Vec4::ZERO ||_renderingType==RenderingType::SIMPLE) ? ui::Scale9Sprite::RenderingType::SIMPLE : ui::Scale9Sprite::RenderingType::SLICE);
    sprite->setCapInsets(calcMargins(margins, size));
    sprite->setBlendFunc(getNodeParamValue(params, PROPERTY_BLENDFUNC, _blendFunc));
    const std::pair<bool,bool> &flipped = getNodeParamValue(params, PROPERTY_FLIP, _flipped);
    sprite->setFlippedX(flipped.first);
    sprite->setFlippedY(flipped.second);
    
    const SpriteFrameDescription &spriteFrame = getNodeParamValue(params, PROPERTY_SPRITEFRAME, _spriteFrame);
    sprite->setName(spriteFrame.path);
}

Scale9SpriteLoader::Scale9SpriteLoader()
    :_blendFunc(BlendFunc::ALPHA_PREMULTIPLIED)
    ,_flipped(false, false)
    ,_renderingType(RenderingType::AUTO)
{
    
}
Scale9SpriteLoader::~Scale9SpriteLoader(){
    
}
    
void Scale9SpriteLoader::onHandlePropTypeBlendFunc(const std::string &propertyName, bool isExtraProp, const BlendFunc &value) {
    if(propertyName == PROPERTY_BLENDFUNC) {
        _blendFunc = value;
    } else {
        NodeLoader::onHandlePropTypeBlendFunc(propertyName, isExtraProp, value);
    }
}
    
void Scale9SpriteLoader::onHandlePropTypeSpriteFrame(const std::string &propertyName, bool isExtraProp, const SpriteFrameDescription &value)
{
    if(propertyName == PROPERTY_SPRITEFRAME) {
        _spriteFrame = value;
    } else {
        NodeLoader::onHandlePropTypeSpriteFrame(propertyName, isExtraProp, value);
    }
}
    
void Scale9SpriteLoader::onHandlePropTypeOffsets(const std::string &propertyName, bool isExtraProp, const Vec4 &value)
{
    if(propertyName == PROPERTY_MARGIN) {
        _margins = value;
    } else {
        NodeLoader::onHandlePropTypeOffsets(propertyName, isExtraProp, value);
    }
}

void Scale9SpriteLoader::onHandlePropTypeFloat(const std::string &propertyName, bool isExtraProp, float value)
{
    if(propertyName == PROPERTY_MARGIN_LEFT) {
        _margins.x = value;
    } else if(propertyName == PROPERTY_MARGIN_TOP) {
        _margins.y = value;
    } else if(propertyName == PROPERTY_MARGIN_RIGHT) {
        _margins.z = value;
    } else if(propertyName == PROPERTY_MARGIN_BOTTOM) {
        _margins.w = value;
    } else {
        NodeLoader::onHandlePropTypeFloat(propertyName, isExtraProp, value);
    }
}
    
void Scale9SpriteLoader::onHandlePropTypeFlip(const std::string &propertyName, bool isExtraProp, const std::pair<bool,bool> &value)
{
    if(propertyName == PROPERTY_FLIP) {
        _flipped = value;
    } else {
        NodeLoader::onHandlePropTypeFlip(propertyName, isExtraProp, value);
    }
}
    
void Scale9SpriteLoader::onHandlePropTypeIntegerLabeled(const std::string &propertyName, bool isExtraProp, int value)
{
    if(propertyName == PROPERTY_RENDERINGTYPE) {
        _renderingType = static_cast<RenderingType>(value);
        assert(_renderingType != RenderingType::TILED);
    } else {
        NodeLoader::onHandlePropTypeIntegerLabeled(propertyName, isExtraProp, value);
    }
}

}

NS_CC_END
