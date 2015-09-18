(ns pso.core
  (:use clojure.core func.core
        [clojure.pprint :only [pprint]])
  (:require [clojure.core.matrix :as mat]
            [clojure.core.matrix.operators :as op]
            [clojure.core.matrix.linear    :refer [norm]]
            ;; [clojure.core.async :refer [chan buffer go go-loop timeout >! >!! <! <!! close! alt!]]
            [incanter.stats      :as stats]
            )
  (:import [mikera.matrixx Matrix]
           [mikera.vectorz Vector]))

(set! *warn-on-reflection* true)

(mat/set-current-implementation :vectorz)

(defn v-max-fn
  "Update v_max"
  ^Double
  [^Double std]
  (if (> std 1.0)
    (Math/log (unchecked-inc std))
    (Math/log (unchecked-inc (* std std)))))

(defn new-v-max
  "determine new v-max"
  [^Vector position-std & {:keys [^Double curr]
                           :or   {curr Double/MAX_VALUE}}]
  (let [len ^Integer (.length position-std)
        v   ^Vector  (Vector/createLength len)]
    (loop [i ^Integer (int 0)]
      (if (< i len)
        (do
         (.set v i ^Double (v-max-fn (mat/mget position-std i)))
         (recur (unchecked-inc-int i)))
        (let [v-max (norm v)]
          (if (>= v-max curr)
            curr
            v-max))))))

(defn seed-particles
  "Seeding agents' initial positions, based on range and dimension number"
  [particle-count search-ranges]
  (let [[dim _] (mat/shape search-ranges)
        m       (Matrix/create dim particle-count)]
    ;; (print m)
    (loop [r ^Integer (int 0)]
      (if (< r dim)
        (let [start (mat/mget search-ranges r 0)
              end   (mat/mget search-ranges r 1)
              range (- end start)]
          (loop [c ^Integer (int 0)]
            (when (< c particle-count)
              (.set m r c (+ start (* (Math/random) range)))
              (recur (unchecked-inc-int c))))
          (recur (unchecked-inc-int r)))
        m))))

(defn pos-sd
  "Find the stand deviation of each dimension"
  ^Vector
  [pos]
  (let [[dim _]        (mat/shape pos)
        sd-mat ^Vector (Vector/createLength dim)]
    (loop [i ^Integer (int 0)]
      (when (< i dim)
        (.set sd-mat i ^Double (stats/sd (mat/select i :all)))
        (recur (unchecked-inc-int i))))
    sd-mat))

(defn update-pos
  "Update swarm particles' position"
  [v]
  (let [[_ particle-count] (mat/shape v)
        r_a1 (Matrix/createRandom 1 particle-count)
        r_a2 (Matrix/createRandom 1 particle-count)]
    ))

(defn search
  "Particle swarm search:
  update scheme:
      x(k + 1) = x(k) + v(k)
      v(k + 1) = w.v(k) + r(0, a_1).(x_localbest(k) - x(k)) + r(0, a_2).(x_globalbest(k) - x(k))
  w: should be between [0.9, 1.2]
  search-range: a n by 2 matrix, row number indicates the dimension number
                each row indicates the search range for that dimension
  "
  [func & {:keys [particle-count  search-range w a1 a2 debug]
           :or   {particle-count  (long 100)
                  search-range (mat/matrix :vectorz [[-10 10]])
                  w            1
                  a1           1
                  a2           2
                  debug        false}}]

  (let [[row col] (mat/shape search-range)
        init-pos  (seed-particles particle-count search-range)
        cores     (.availableProcessors (Runtime/getRuntime))]
    (if debug
      (pprint {:count particle-count
               :range search-range
               :dim   row
               :col   col}))
    )

  )
