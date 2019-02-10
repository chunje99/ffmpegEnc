
public class JNITest {
    JNITest(){
        try {
            System.loadLibrary("jnifenc");
        } catch(UnsatisfiedLinkError e) {
            System.out.println(e);
            System.exit(1);
        }
        cppIns = CreateNI();
    }
    public void PRINT(){
        Print(cppIns);
    }
    public void SetSource(String str){
        setSource(cppIns, str);
    }
    public String GetSource(){
        return getSource(cppIns);
    }
    public void SetTarget(String str){
        setTarget(cppIns, str);
    }
    public String GetTarget(){
        return getTarget(cppIns);
    }
    public void SetPreset(String str){
        setPreset(cppIns, str);
    }
    public String GetPreset(){
        return getPreset(cppIns);
    }
    public void SetThumbnailTime(int ttime){
        setThumbnailTime(cppIns, ttime);
    }
    public int GetThumbnailTime(){
        return getThumbnailTime(cppIns);
    }
    public void StartEnc(){
        StartEncode(cppIns);
    }
    public void StartThumb(){
        StartThumbnail(cppIns);
    }
    public void WAIT(){
        Wait(cppIns);
    }

    private long cppIns;

    private native long CreateNI();
    private native void DeleteNI(long cppIns);
    private native void Print(long cppIns);
    private native void setSource(long cppIns, String src);
    private native String getSource(long cppIns);
    private native void setTarget(long cppIns, String src);
    private native String getTarget(long cppIns);
    private native void setPreset(long cppIns, String src);
    private native String getPreset(long cppIns);
    private native void setThumbnailTime(long cppIns, int ttime);
    private native int getThumbnailTime(long cppIns);
    private native void StartEncode(long cppIns);
    private native void StartThumbnail(long cppIns);
    private native void Wait(long cppIns);

    public static void main(String[] args){
        //System.out.println(System.getProperty("java.library.path"));
        JNITest jtest = new JNITest();
        //jtest.cppIns = jtest.CreateNI();
        //jtest.Print(jtest.cppIns);
        jtest.PRINT();
        jtest.SetSource("/home/ho80/다운로드/a_h_e152.mp4");
        System.out.println(jtest.GetSource());
        jtest.SetTarget("out.mp4");
        System.out.println(jtest.GetTarget());
        jtest.SetPreset("SD");
        System.out.println(jtest.GetPreset());
        jtest.StartEnc();
        jtest.WAIT();
    }
}
