(ns func.core
  (:use [clojure.core]))

(defn mk-ackley
  "Create a new ackley function with given parameters a, b, c"
  [^Double a ^Double b ^Double c]
  (fn [x]
    (let [n (count x)]
      (+ (* (- a)
            (Math/exp (* (- b) (Math/sqrt (/ (apply + (map #(* % %) x)) n)))))
         (- (Math/exp (/ (apply + (map #(Math/cos (* c %)) x)) n)))
         a
         Math/E))))

(defn mk-michalewicz
  "Create a new Michalewicz function with given parameter m."
  [^Double m]
  (fn [x]
    (- (apply + (map #(* (Math/sin %1)
                         (Math/pow (Math/sin (/ (* %2 %1 %1) Math/PI)) (* 2 m)))
                     x (range 1 (inc (count x))))))))

(defn rastrigin
  "Rastrigin function."
  [x]
  (apply +
         (* 10 (count x))
         (map #(- (* % %) (* 10 (Math/cos (* 2 Math/PI %)))) x)))
