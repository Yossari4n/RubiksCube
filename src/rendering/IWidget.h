#ifndef IWidget_h
#define IWidget_h

class IWidget {
public:
    enum class EAlign {
        NONE,
        BEGIN,
        CENTER,
        END
    };

    IWidget() = default;
    virtual ~IWidget() = default;
    IWidget(const IWidget&) = delete;
    IWidget& operator=(const IWidget&) = delete;
    IWidget(IWidget&&) = delete;
    IWidget& operator=(IWidget&&) = delete;

    virtual void Draw() const = 0;

protected:
    template <class T>
    void Align(T* value, const T& min, const T& max, EAlign align) const {
        if (align == EAlign::NONE) {
            return;
        }

        if (align == EAlign::BEGIN) {
            *value = min;
            return;
        } else if (align == EAlign::CENTER) {
            *value = (min + max) / 2;
            return;
        } else /*align == EAling::END*/ {
            *value = max;
            return;
        }
    }
};

#endif