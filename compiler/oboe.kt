/* Sigma.scala
 *
 * Compute sum = 1 + 2 + ... + n
 */

class oboe
{
  // constants and variables
  var n
  val str = "sadasd"
  val xx = 33
  var sum: int
  var index: int
  val zzz : int = 5+3 * xx
    var xxxxx = zzz - xx
  var b = true

  fun div(x:int,y:int):int
  {
    
    return x-y
  }
  

  fun fib(n:int):int {
    if(n<2)
      return n
    else
      return fib(n-1) + fib(n-2)
  }





  fun add(a:int,b:int):int{
    var sum = a+b

    return sum
  }

  fun myprint(n:int,flag:boolean){
    var a = n+n*n
    val c = 10000
    print("c is ")
    println(c)
    println(a)
    if(flag == false){
       println("flag false")
       if(a < c){
         print("a is smaller than c and a is ")
         println(a)
       }
       else{
         print("a is")
         println(a)
       }
    }
    else
      println("flag true")
    sum = add(sum,n)

    val flag1 = false
    val flag2 = false
    print("flag compute ans ")
    println(flag1 | flag2)
  }

  fun main () {
    sum = 1
    index = 0
    n = 1
    print(xx)
    /*while(n<=10){
      print(str)
      n = n + 1
    }*/

    print ("The sum is")
    println (sum)
    println(index)
    var i = 0
    if(i <= 0){
      println("i <= 0")
      if(sum == 0 ){
        println("sum=0")
      }
      else{
        println("sum!=0")
      }
    }
     if (i>=0){
      println("i>=0")
    }
    else{
      println("i!= 1 or 0 ")
    }
    for(sum in 10 .. 10){
      println(index)
      index = index + 1
      for(i in 0 .. 10){
        print(i)
        index = index + 1
      }
      println("")
    } 
    println(index)
    i = 0
    val start = 0
    var end
    end = 4
    for(i in 0 ..  4){
      print("i = ")
      println(add(i,1))
      println(fib(i))
      
    }
    end = 1

    if(end==1)
      println("end = 1")

    println("call void")
    println("sum is")
    val flag = false
    myprint(10,flag)
    println(sum)
    sum = 5
    println((sum==5) | (sum==3))

    println(div(3,2))
  }
}
