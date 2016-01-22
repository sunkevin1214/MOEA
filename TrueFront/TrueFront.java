/**
 * 
 */
package many_object;

/**
 * @author Administrator
 *
 */
public class TrueFront {

	/**
	 * get the true Pareto front file of specific problem
	 * @param numberOfObjectives
	 * @param problemName
	 * @return
	 */
	public static String getTPFile(int numberOfObjectives, String problemName) {
		String classpath = TrueFront.class.getClass().getResource("/").toString()+"many_object";
		classpath = classpath.substring(6) + "/" + problemName.toLowerCase() + "_tf_" + numberOfObjectives + "objs.txt";
//		System.out.println(classpath);
		return classpath;
	}
	
	public static void main(String[] args) {
		System.out.println(TrueFront.getTPFile(3, "DTLZ1".toLowerCase()));
	}
}
