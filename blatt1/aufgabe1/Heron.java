public class Heron {
	private static final float EPS1M24 = 1.0f - (float) Math.pow(2, -24);
	private static final float EPS1P24 = 1.0f + (float) Math.pow(2, -24);
	
	public static void main(String[] args) {
		for (int i = 0; i < args.length; i++) {
			float a = Float.parseFloat(args[i]);
			float x = mulInverse(a);
			
			System.out.printf("a: %f, x: %f, a*x: %f\n", a, x, a * x);
		}
	}
	
	public static float mulInverse(float a) {
		float x = 1.0f;
		float p;
		
		// first approximation loop
		while (true) {
			p = a * x;
			if (p < 0.5f) {
				x *= 2.0f;
			} else if (p > 1.5f) {
				x *= 0.5f;
			} else {
				break;
			}
		}
		
		// refinement loop
		while (true) {
			p = a * x;
			if (p < EPS1M24 || p > EPS1P24) {
				x *= 2.0f - p;
			} else {
				break;
			}
		}
		
		return x;
	}
}
