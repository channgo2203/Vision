package com.codertimo.sidewalkdetection.algorithm.type;

/**
 * Created by codertimo on 2015. 12. 17..
 */
public class ComparableLine {
    /**
     * lenth : 선분의 길이
     * slope : 직선의 기울기
     * point : 직선의 두 점의 좌표
     */
    public int lenth =0;
    public double slope =0.0;
    public Vec4i point = null;

    /**
     * 내부 변수들에 대한 설명 : Vec4i vec : 입력시 받은 2개의 점(x1,y1),(x2,y2)순서
     * 설명 : 생성자이며, 기본적인 정보를 설정한다.
     */
    public ComparableLine(Vec4i vec){

        this.point = vec;

        this.lenth = (int)Math.pow(point.x1-point.x2,2) +(int) Math.pow(point.y1-point.y2,2);
        //길이에 루트 씌워줘야 하는거 아닌가

        if(point.x1 == point.x2)
            slope = 90; // 0으로 나눌려면 90도로 미리 처리
        else
            slope = Math.atan(-1 * (point.y2 - point.y1)/(point.x2 - point.x1)) * 180.0 /Math.PI;
            // 아니면 arctan, 호도법으로 DMS Notation으로 전환

        if(slope < 0) // 각도는 0~180도 까지만 허용, 만약 이를 초과시 180+해서 수정
            slope += 180;
    }

}
