#include"matrix.h"

class EVD{
public:
    pp::vec w;
    matrix V;
    static void timesJ(matrix& A, int p, int q, double theta);
    static void Jtimes(matrix& A, int p, int q, double theta);
    EVD(matrix A, bool is_sym = false){
        V = identity(A.nrows); // This is a copy operator because identity only exists temporary
        w = pp::vec (A.nrows); // This is a copy operator only exists temporary.
        bool changed = true;
        if (!is_sym){
            do{
            
                changed = false;
                for(int p=0;p<A.nrows-1;p++)
                for(int q=p+1;q<A.nrows;q++){
                    double apq = A[p,q], app = A[p,p], aqq = A[q,q];
                    double theta = 0.5*std::atan2(2*apq, aqq - app);
                    double c = std::cos(theta), s = std::sin(theta);
                    double new_app = c*c*app - 2*s*c*apq + s*s*aqq;
                    double new_aqq = s*s*app + 2*s*c*apq + c*c*aqq;
                    if(new_app!=app || new_aqq!=aqq){ // do rotation
                        changed=true;
                        timesJ(A, p, q, theta); // A←A*J 
                        Jtimes(A, p, q, -theta); // A←JT*A
                        timesJ(V, p, q, theta); // V←V*J
                        }
                }
            }while(changed);
        }
        else {
            do{
                changed = false;
                for(int p=0;p<A.nrows-1;p++)
                for(int q=p+1;q<A.nrows;q++){
                    double apq = A[p,q], app = A[p,p], aqq = A[q,q];
                    double theta = 0.5*std::atan2(2*apq, aqq - app);
                    double c = std::cos(theta), s = std::sin(theta);
                    double new_app = c*c*app - 2*s*c*apq + s*s*aqq;
                    double new_aqq = s*s*app + 2*s*c*apq + c*c*aqq;
                    if(new_app!=app || new_aqq!=aqq){
                        changed = true;
                            for(int i=0;i<A.nrows;i++){
                                if(i!=p && i!=q){
                                    double aip = A[i, p], aiq = A[i, q];

                                    A[i, p] = c*aip - s*aiq;
                                    A[p, i] = A[i, p];

                                    A[i, q] = s*aip + c*aiq;
                                    A[q, i] = A[i, q];
                                }
                            }

                            A[p, p] = c*c*app - 2*s*c*apq + s*s*aqq;
                            A[q, q] = s*s*app + 2*s*c*apq + c*c*aqq;

                            A[p, q] = 0;
                            A[q, p] = 0;
                        }
                    }
                }while(changed);
            }
        for (int i = 0; i < w.size();++i){
            w[i] = A[i, i];
            }
        }
};
