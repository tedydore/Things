package com.tedydore.mathtests;

import java.math.BigDecimal;
import java.math.MathContext;

public class Main {
	
	public static void main(String[] args) {
		
		String all = null;

		int expo;
		String[] mult = {" ","K","M","G","T","tr","sx","sq"};
		//Prefix (for each thousand of thousands of number (1, 1.000, 1.000.000, etc))
		
		double d = 712962325568219893434823f;
		//Current Energy
		
		for (int cont = 0; cont<3000; cont++) {
		//Cycle for speed test
		double deb = d;
		
		BigDecimal bd = new BigDecimal(deb);
		bd = bd.round(new MathContext(4));
		String test = bd.toPlainString();
		//BigDecimal - object with methods round and toPlainString
		expo = test.length();
		
		if (expo>3 && expo%3!=0) {
			int point = expo%3;
			int counter = 0;
			while (deb>999) {
				deb = deb/1000;
				counter++;
			}
			String current = test.substring(0,4);
			all = current+mult[counter];
			if (point > 0) {
				String first = current.substring(0, point);
				String second = current.substring(point, 4);
				all = first+'.'+second+mult[counter];
			} else {all = current+'.'+mult[counter];}
		} else {
			int counter = 0;
			while (deb>999) {
				deb = deb/1000;
				counter++;
			}
			if (expo>3) {
				String first = test.substring(0, 3);
				all = first+'.'+mult[counter];
			} else {all = test+'.'+mult[counter];}
		}
		
		if (all.length() == 5) {all = '0'+all;} 
		else if (all.length() == 4) {all = "00"+all;}
		else if (all.length() == 3) {all = "000"+all;}
		
		System.out.println(all);
		//Final string
		}
		
		System.out.println("The End");
	}


}
