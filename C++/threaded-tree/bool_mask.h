#ifndef _QP_BOOL_MASK_H_
#define _QP_BOOL_MASK_H_

class bool_mask {
    private:
        char c_;
    public:
        bool_mask() : c_(0) {};
        void set(const unsigned int i) {
            c_ |= 1 << i;
        }
        void unset(const unsigned int i) {
            c_ &= ~(1 << i);
        }
        bool operator [](const unsigned int i) const {
            return c_ & (1 << i);
        }
};

#endif
