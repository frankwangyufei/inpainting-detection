//
// Created by antoinewdg on 11/27/16.
//

#ifndef INPAINTING_DECTECTION_PATCH_DISTANCE_H
#define INPAINTING_DECTECTION_PATCH_DISTANCE_H

#include "utils.h"

/**
 * Radiometric distance between two patches.
 * @tparam P patch size
 */
template<int P>
class PatchDistance {
public:
    typedef Vec2i left_type;
    typedef Vec2i right_type;
    typedef int output_type;

    PatchDistance(Mat_<Vec3b> s, unsigned int min_offset) :
            m_s(s), m_min_sqr_offset(min_offset * min_offset) {
    }

    inline output_type operator()(const left_type &p, const right_type &q) {
        return operator()(p, q, std::numeric_limits<output_type>::max());
    }

    /**
     * Compute the distance between two patches.
     *
     * The offset between the patches must be big enough,
     * else the distance if infinite.
     *
     * @param p
     * @param q
     * @param max_d maximum value of the distance, used for early stopping
     * @return
     */
    inline output_type operator()(const left_type &p, const right_type &q, output_type max_d) {

        if (_offset_too_small(p, q)) {
            return std::numeric_limits<output_type>::max();
        }

        output_type d(0);
        for (int i = -P / 2; i <= P / 2; i++) {
            for (int j = -P / 2; j <= P / 2; j++) {
                Vec2i u = p + Vec2i(i, j);
                Vec2i v = q + Vec2i(i, j);

                for (int c = 0; c < 3; c++) {
                    int temp = m_s(u)[c] - m_s(v)[c];
                    d += temp * temp;
                }

                // Check for early stopping
                if (d >= max_d) {
                    return d;
                }
            }
        }
        return d;
    }

private:

    inline bool _offset_too_small(const Vec2i &p, const Vec2i &q) {
        int a = p[0] - q[0];
        int b = p[1] - q[1];
        return a * a + b * b <= m_min_sqr_offset;
    }

    Mat_<Vec3b> m_s;
    output_type m_min_sqr_offset;
};

#endif //INPAINTING_DECTECTION_PATCH_DISTANCE_H
