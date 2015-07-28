/* 
 * File:   UF.h
 * Author: tuannguyen
 *
 * Created on 5 July 2015, 8:47 PM
 */

#ifndef UF_H
#define	UF_H

class UF {
public:
    UF(int N);
    int find(int p);
    int count();
    void join(int p, int q);
    bool connected(int p, int q);
    
private:
    int *id;
    int *sz;
    int cnt;
};

#endif	/* UF_H */

