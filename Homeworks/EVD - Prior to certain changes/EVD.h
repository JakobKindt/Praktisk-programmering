#include"matrix.h"

// Static belongs to a class such that any instance if that class has the same static thing. So it belongs to the class instead of the individual instance.
class EVD{
public:
    pp::vec<double> w;
    matrix V;
    static void timesJ(matrix& A, int p, int q, double theta);
    static void Jtimes(matrix& A, int p, int q, double theta);
    EVD(matrix& A){
        // matrix Id = identity(M.nrows); 
        // pp::vec<double> vessel(M.nrows);
        // V = Id; // This is a moce operator because Id exists outside of this line.
        // w = vessel; // This is a move operator because vessel exists outside of this line.
        V = identity(A.nrows); // This is a copy operator because identity only exists temporary
        w = pp::vec<double> (A.nrows); // This is a copy operator only exists temporary.
        // V.print("initial V=");
        /* run Jacobi rotations on A and update V */
        bool changed = true;
        while (changed){
            changed = false;
            for(int p=0;p<A.nrows-1;p++)
            for(int q=p+1;q<A.nrows;q++){
		    // std::cerr<< "p="<<p<<" q="<<q<<"\n";
                double apq = A[p,q], app = A[p,p], aqq = A[q,q];
                double theta = 0.5*std::atan2(2*apq, aqq - app);
                double c = std::cos(theta), s = std::sin(theta);
                double new_app = c*c*app - 2*s*c*apq + s*s*aqq;
                double new_aqq = s*s*app + 2*s*c*apq + c*c*aqq;
            // std::cerr << "Theta = " << theta << "\n";
		    // std::cerr<< "app = "<<app<<" aqq = "<<aqq<<"\n";
		    // std::cerr<< "new_app = "<<new_app<<" new_aqq = "<<new_aqq<<"\n";
                if(new_app!=app || new_aqq!=aqq) // do rotation
                // if(!pp::approx(new_app, app) || !pp::approx(new_aqq, aqq)) // do rotation
                    {
                    changed=true;
                    timesJ(A, p, q, theta); // A←A*J 
                    Jtimes(A, p, q, -theta); // A←JT*A 
                    timesJ(V, p, q, theta); // V←V*J
                    }
                // changed=false;
            }
        }
        /* copy diagonal elements into w */
        for (int i = 0; i < w.size();++i){
            w[i] = A[i, i];
        }
        }
};



// #include"matrix.h"

// // Static belongs to a class such that any instance if that class has the same static thing. So it belongs to the class instead of the individual instance.
// class EVD{
// public:
//     pp::vec<double> w;
//     matrix V;
//     static void timesJ(matrix& A, int p, int q, double theta);
//     static void Jtimes(matrix& A, int p, int q, double theta);
//     EVD(matrix& A){
//         // matrix Id = identity(M.nrows); 
//         // pp::vec<double> vessel(M.nrows);
//         // V = Id; // This is a moce operator because Id exists outside of this line.
//         // w = vessel; // This is a move operator because vessel exists outside of this line.
//         V = identity(A.nrows); // This is a copy operator because identity only exists temporary
//         w = pp::vec<double> (A.nrows); // This is a copy operator only exists temporary.
//         // V.print("initial V=");
//         /* run Jacobi rotations on A and update V */
//         bool changed = true;
//         while (changed){
//             changed = false;
//             for(int p=0;p<A.nrows-1;p++)
//             for(int q=p+1;q<A.nrows;q++){
// 		    // std::cerr<< "p="<<p<<" q="<<q<<"\n";
//                 double apq = A[p,q], app = A[p,p], aqq = A[q,q];
//                 double theta = 0.5*std::atan2(2*apq, aqq - app);
//                 double c = std::cos(theta), s = std::sin(theta);
//                 double new_app = c*c*app - 2*s*c*apq + s*s*aqq;
//                 double new_aqq = s*s*app + 2*s*c*apq + c*c*aqq;
//             // std::cerr << "Theta = " << theta << "\n";
// 		    // std::cerr<< "app = "<<app<<" aqq = "<<aqq<<"\n";
// 		    // std::cerr<< "new_app = "<<new_app<<" new_aqq = "<<new_aqq<<"\n";
//                 // if(new_app!=app || new_aqq!=aqq) // do rotation
//                 if(!pp::approx(new_app, app) || !pp::approx(new_aqq, aqq)) // do rotation
//                     {
//                     changed=true;
//                     timesJ(A, p, q, theta); // A←A*J 
//                     Jtimes(A, p, q, -theta); // A←JT*A 
//                     timesJ(V, p, q, theta); // V←V*J
//                     }
//                 // changed=false;
//             }
//         }
//         /* copy diagonal elements into w */
//         for (int i = 0; i < w.size();++i){
//             w[i] = A[i, i];
//         }
//         }
// };
