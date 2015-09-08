(ns pso.core
  (:use func.core
        [clojure.pprint :only [pprint]])
  (:require [clojure.core.matrix :as mat]
            [clojure.core.matrix.operators :as op]
            ;; [clojure.core.async :refer [chan buffer go go-loop timeout >! >!! <! <!! close! alt!]]
            ))

(set! *warn-on-reflection* true)

(mat/set-current-implementation :vectorz)

(defn search
  "Particle swarm search:
  update scheme:
      x(k + 1) = x(k) + v(k)
      v(k + 1) = w.v(k) +
                 r(0, a_1).(x_localbest(k) - x(k)) +
                 r(0, a_2).(x_globalbest(k) - x(k))
  w: should between [0.9, 1.2]"
  [func & {:keys [agent-count search-range]
           :or   {agent-count 100
                  search-range [-10 10]}}]
  )
