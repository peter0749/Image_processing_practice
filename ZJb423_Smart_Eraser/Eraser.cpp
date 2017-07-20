#ifndef __ERASER_CLASS_REQUIRE_ONCE
#define __ERASER_CLASS_REQUIRE_ONCE
#include "Eraser.h"

namespace ImageProcess 
{
#define EPS 1e-12
    // Compute rgb diff between two pixels
    double Eraser::pixDist(const Pix &a, const Pix &b) {
        double dr = a.r-b.r;
        double dg = a.g-b.g;
        double db = a.b-b.b;
        return std::sqrt(dr*dr+dg*dg+db*db);
    }
    void Eraser::processWholeImg() {
        int imgW = this->data->img_W;
        int imgH = this->data->img_H;
        Pix targetCol = this->data->data[opY*imgW+opX];
        for (int i=0; i<imgH; ++i) {
            for (int j=0; j<imgW; ++j) {
                if (pixDist(this->data->data[i*imgW+j], targetCol) < diff + EPS) this->data->data[i*imgW+j].alpha=0;
            }
        }
    }

    void Eraser::processAdjacingPix() {
        using std::queue;
        using std::pair;
        using std::make_pair;
        const pair<int,int> dir[4] = { // X , Y diff
            pair<int,int>(1,0),
            pair<int,int>(0,1),
            pair<int,int>(-1,0),
            pair<int,int>(0,-1),
        };
        int imgW = this->data->img_W;
        int imgH = this->data->img_H;
        Pix targetCol = this->data->data[opY*imgW+opX];
        queue< pair<int,int> > que; // store <X, Y> pair
#define X first
#define Y second
        bool *vis = NULL;
        vis = new bool[imgW*imgH]; 
        // 另外開一個紀錄拜訪的陣列，
        // 因為我認為只靠 alpha == 0 來判斷是否走過，不太合邏輯（因為 alpha 可能本來就為 0）
        if (vis==NULL) throw std::runtime_error("visit table is NULL!");
        memset(vis, 0x00, sizeof(bool)*imgW*imgH);
        this->data->data[opY*imgW+opX].alpha = 0; // 不論如何，進入點必須去背
        vis[opY*imgW+opX] = true; // 標記為已拜訪
        que.push(make_pair(opX, opY));
        while(!que.empty()) {
            pair<int,int> inst = que.front(); que.pop();
            for (int i=0; i<4; ++i) {
                pair<int,int> nC(inst.X+dir[i].X, inst.Y+dir[i].Y);
                if (nC.X>=0 && nC.X<imgW && nC.Y>=0 && nC.Y<imgH && \
                        !vis[nC.Y*imgW+nC.X] && pixDist(this->data->data[nC.Y*imgW+nC.X], targetCol) < diff + EPS) {
                    this->data->data[nC.Y*imgW+nC.X].alpha = 0;
                    vis[nC.Y*imgW+nC.X] = true;
                    que.push(nC);
                }
            }
        }
        delete[] vis; vis=NULL;
#undef X
#undef Y
    }
    Eraser::Eraser( Image *imgData, int mode,\
            int selectX, int selectY, double diff=0.3) : \
        mode(mode), opX(selectX), opY(selectY), diff(diff) {
            this->data = imgData;
            if (this->data==NULL) throw std::runtime_error("pointer of image object is a NULL pointer");
            if (this->diff < 0.0) throw std::runtime_error("diff is negative!");
            if (this->mode!=0 && this->mode!=1) 
                throw std::runtime_error("mode is not 0/1");
            if (this->opX < 0 || this->opX >= (int)data->img_W || this->opY < 0 || this->opY >= (int)data->img_H) 
                throw std::runtime_error("selected coordinate out of range");
        }

    void Eraser::run(void) {
        switch(this->mode) {
            case 0:
                this->processWholeImg();
                break;
            case 1:
                this->processAdjacingPix();
                break;
            default:
                throw std::runtime_error("mode is not 0/1 (this shouldn't happen :( )");
                break;
        }
    }
#undef EPS
};
#endif
