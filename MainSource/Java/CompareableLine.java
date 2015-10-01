
class CompareableLine{
  //상수
  static final double sdAllowedMinGap = 0.9;
  static final double sdAllowedMaxGap = 1.1;
  static final double sdDeniedMinGap = 0.8;
  static final double sdDeniedMaxGap = 1.2;
  static final double cdParameter_beta = 0.0001;

  //변수
  private int iLine_size;
  private double dSlope;
  private double sdAvgLineSize;
  private double sdAvgCubeLineSize;
  private Vec4i vPoint;

  //생성자
  public CompareableLine(){}
  public CompareableLine(Vect4i point){}

  //내부 함수
  public Vec4i getPoint()
  public int getLine_size()
  public double getFunctionD(double)
  public double getFunctionS(double)
  public double getSlope()
  public boolean calParams()

  //전역 함수
  public static void setAvgLineSize(double)
  public static void setAvgCubeLineSize(double)
  public static double getAvgLineSize()
}
